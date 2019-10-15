#ifndef STATIC_RTREE_HPP
#define STATIC_RTREE_HPP

#include "util/bearing.hpp"
#include "util/coordinate_calculation.hpp"
#include "util/deallocating_vector.hpp"
#include "util/exception.hpp"
#include "util/hilbert_value.hpp"
#include "util/integer_range.hpp"
#include "util/rectangle.hpp"
#include "util/shared_memory_vector_wrapper.hpp"
#include "util/typedefs.hpp"
#include "util/web_mercator.hpp"

#include "osrm/coordinate.hpp"

#include <boost/assert.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/format.hpp>
#include <boost/iostreams/device/mapped_file.hpp>

#include <tbb/parallel_for.h>
#include <tbb/parallel_sort.h>

#include <algorithm>
#include <array>
#include <limits>
#include <memory>
#include <queue>
#include <string>
#include <vector>


#include "../../src/protobuf/rtree.pb.h"
#include "../../src/protobuf/edge-based-graph.pb.h"

// An extended alignment is implementation-defined, so use compiler attributes
// until alignas(LEAF_PAGE_SIZE) is compiler-independent.
#if defined(_MSC_VER)
#define ALIGNED(x) __declspec(align(x))
#elif defined(__GNUC__)
#define ALIGNED(x) __attribute__((aligned(x)))
#else
#define ALIGNED(x)
#endif

static int _debug = 0;

template <class T, class S, class C>
S& Container(std::priority_queue<T, S, C>& q) {
    struct HackedQueue : private std::priority_queue<T, S, C> {
        static S& Container(std::priority_queue<T, S, C>& q) {
            return q.*&HackedQueue::c;
        }
    };
    return HackedQueue::Container(q);
}

namespace osrm
{
namespace util
{

    void printRectangle(const osrm::util::RectangleInt2D &rectangle) {
        std::cout << "    - mbr: "
                  << "top: " << int32_t(rectangle.max_lat) << ", "
                  << "bottom: " << int32_t(rectangle.min_lat) << ", "
                  << "left: " << int32_t(rectangle.min_lon) << ", "
                  << "right: " << int32_t(rectangle.max_lon) << std::endl;
    }


    // Static RTree for serving nearest neighbour queries
// All coordinates are pojected first to Web Mercator before the bounding boxes
// are computed, this means the internal distance metric doesn not represent meters!
template <class EdgeDataT,
          class CoordinateListT = std::vector<Coordinate>,
          bool UseSharedMemory = false,
          std::uint32_t BRANCHING_FACTOR = 128,
          std::uint32_t LEAF_PAGE_SIZE = 4096>
class StaticRTree
{
  public:
    using Rectangle = RectangleInt2D;
    using EdgeData = EdgeDataT;
    using CoordinateList = CoordinateListT;

    static_assert(LEAF_PAGE_SIZE >= sizeof(uint32_t) + sizeof(EdgeDataT), "page size is too small");
    static_assert(((LEAF_PAGE_SIZE - 1) & LEAF_PAGE_SIZE) == 0, "page size is not a power of 2");
    static constexpr std::uint32_t LEAF_NODE_SIZE =
        (LEAF_PAGE_SIZE - sizeof(uint32_t) - sizeof(Rectangle)) / sizeof(EdgeDataT);

    struct CandidateSegment
    {
        Coordinate fixed_projected_coordinate;
        EdgeDataT data;
    };

    struct TreeIndex
    {
        TreeIndex() : index(0), is_leaf(false) {}
        TreeIndex(std::size_t index, bool is_leaf) : index(index), is_leaf(is_leaf) {}
        std::uint32_t index : 31;
        std::uint32_t is_leaf : 1;
    };

    struct TreeNode
    {
        TreeNode() : child_count(0) {}
        std::uint32_t child_count;
        Rectangle minimum_bounding_rectangle;
        TreeIndex children[BRANCHING_FACTOR];
    };

    struct ALIGNED(LEAF_PAGE_SIZE) LeafNode
    {
        LeafNode() : object_count(0), objects() {}
        std::uint32_t object_count;
        Rectangle minimum_bounding_rectangle;
        std::array<EdgeDataT, LEAF_NODE_SIZE> objects;
    };
    static_assert(sizeof(LeafNode) == LEAF_PAGE_SIZE, "LeafNode size does not fit the page size");

  private:
    struct WrappedInputElement
    {
        explicit WrappedInputElement(const uint64_t _hilbert_value,
                                     const std::uint32_t _array_index)
            : m_hilbert_value(_hilbert_value), m_array_index(_array_index)
        {
        }

        WrappedInputElement() : m_hilbert_value(0), m_array_index(UINT_MAX) {}

        uint64_t m_hilbert_value;
        std::uint32_t m_array_index;

        inline bool operator<(const WrappedInputElement &other) const
        {
            return m_hilbert_value < other.m_hilbert_value;
        }
    };

    struct QueryCandidate
    {
        QueryCandidate(std::uint64_t squared_min_dist, TreeIndex tree_index)
            : squared_min_dist(squared_min_dist), tree_index(tree_index),
              segment_index(std::numeric_limits<std::uint32_t>::max())
        {
        }

        QueryCandidate(std::uint64_t squared_min_dist,
                       TreeIndex tree_index,
                       std::uint32_t segment_index,
                       const Coordinate &coordinate)
            : squared_min_dist(squared_min_dist), tree_index(tree_index),
              segment_index(segment_index), fixed_projected_coordinate(coordinate)
        {
        }

        inline bool is_segment() const
        {
            return segment_index != std::numeric_limits<std::uint32_t>::max();
        }

        inline bool operator<(const QueryCandidate &other) const
        {
            // Attn: this is reversed order. std::pq is a max pq!
            return other.squared_min_dist < squared_min_dist;
        }

        std::uint64_t squared_min_dist;
        TreeIndex tree_index;
        std::uint32_t segment_index;
        Coordinate fixed_projected_coordinate;
    };

    typename ShM<TreeNode, UseSharedMemory>::vector m_search_tree;
    const CoordinateListT &m_coordinate_list;

    boost::iostreams::mapped_file_source m_leaves_region;
    // read-only view of leaves
    typename ShM<const LeafNode, true>::vector m_leaves;

  public:
    StaticRTree(const StaticRTree &) = delete;
    StaticRTree &operator=(const StaticRTree &) = delete;

    template <typename CoordinateT>
    // Construct a packed Hilbert-R-Tree with Kamel-Faloutsos algorithm [1]
    explicit StaticRTree(const std::vector<EdgeDataT> &input_data_vector,
                         const std::string &tree_node_filename,
                         const std::string &leaf_node_filename,
                         const std::vector<CoordinateT> &coordinate_list)
        : m_coordinate_list(coordinate_list)
    {
        util::SimpleLogger().Write(logWARNING) << "leaf node size: " << LEAF_NODE_SIZE;

        const uint64_t element_count = input_data_vector.size();
        std::vector<WrappedInputElement> input_wrapper_vector(element_count);

        // generate auxiliary vector of hilbert-values
        tbb::parallel_for(
            tbb::blocked_range<uint64_t>(0, element_count),
            [&input_data_vector, &input_wrapper_vector, this](
                const tbb::blocked_range<uint64_t> &range) {
                for (uint64_t element_counter = range.begin(), end = range.end();
                     element_counter != end;
                     ++element_counter)
                {
                    WrappedInputElement &current_wrapper = input_wrapper_vector[element_counter];
                    current_wrapper.m_array_index = element_counter;

                    EdgeDataT const &current_element = input_data_vector[element_counter];

                    // Get Hilbert-Value for centroid in mercartor projection
                    BOOST_ASSERT(current_element.u < m_coordinate_list.size());
                    BOOST_ASSERT(current_element.v < m_coordinate_list.size());

                    Coordinate current_centroid = coordinate_calculation::centroid(
                        m_coordinate_list[current_element.u], m_coordinate_list[current_element.v]);
                    current_centroid.lat = FixedLatitude{static_cast<std::int32_t>(
                        COORDINATE_PRECISION *
                        web_mercator::latToY(toFloating(current_centroid.lat)))};

                    current_wrapper.m_hilbert_value = hilbertCode(current_centroid);
                }
            });

        // open leaf file
        boost::filesystem::ofstream leaf_node_file(leaf_node_filename, std::ios::binary);

        pbrtree::Leaves pb_leaves;

        // sort the hilbert-value representatives
        tbb::parallel_sort(input_wrapper_vector.begin(), input_wrapper_vector.end());
        std::vector<TreeNode> tree_nodes_in_level;

        // pack M elements into leaf node, write to leaf file and add child index to the parent node
        uint64_t wrapped_element_index = 0;
        uint leaf_count = 0;

        for (std::uint32_t node_index = 0; wrapped_element_index < element_count; ++node_index)
        {
            TreeNode current_node;
            for (std::uint32_t leaf_index = 0;
                 leaf_index < BRANCHING_FACTOR && wrapped_element_index < element_count;
                 ++leaf_index)
            {
                LeafNode current_leaf;

                leaf_count++;

                pbrtree::LeafNode *pb_leaf = pb_leaves.add_items();

                Rectangle &rectangle = current_leaf.minimum_bounding_rectangle;
                for (std::uint32_t object_index = 0;
                     object_index < LEAF_NODE_SIZE && wrapped_element_index < element_count;
                     ++object_index, ++wrapped_element_index)
                {
                    const std::uint32_t input_object_index =
                        input_wrapper_vector[wrapped_element_index].m_array_index;
                    const EdgeDataT &object = input_data_vector[input_object_index];

                    current_leaf.object_count += 1;
                    current_leaf.objects[object_index] = object;

                    pb_leaf->set_itemcount(current_leaf.object_count);
                    pbebg::EdgeBasedNode *pb_ebn = pb_leaf->add_items();
                    extractor::EdgeBasedNode _n = (extractor::EdgeBasedNode)(object);
                    pb_ebn->set_u(_n.u);
                    pb_ebn->set_v(_n.v);
                    pb_ebn->set_forward_enabled(_n.forward_segment_id.enabled);
                    pb_ebn->set_reverse_enabled(_n.reverse_segment_id.enabled);
                    pb_ebn->set_forward_segment_id(_n.forward_segment_id.id);
                    pb_ebn->set_reverse_segment_id(_n.reverse_segment_id.id);
                    pb_ebn->set_forward_packed_geometry_id(_n.forward_packed_geometry_id);
                    pb_ebn->set_reverse_packed_geometry_id(_n.reverse_packed_geometry_id);
                    pb_ebn->set_fwd_segment_position(_n.fwd_segment_position);
                    pb_ebn->set_name_id(_n.name_id);
                    pb_ebn->set_component_id(_n.component.id);
                    pb_ebn->set_is_tiny(_n.component.is_tiny);

                    Coordinate projected_u{
                        web_mercator::fromWGS84(Coordinate{m_coordinate_list[object.u]})};
                    Coordinate projected_v{
                        web_mercator::fromWGS84(Coordinate{m_coordinate_list[object.v]})};

                    BOOST_ASSERT(std::abs(toFloating(projected_u.lon).operator double()) <= 180.);
                    BOOST_ASSERT(std::abs(toFloating(projected_u.lat).operator double()) <= 180.);
                    BOOST_ASSERT(std::abs(toFloating(projected_v.lon).operator double()) <= 180.);
                    BOOST_ASSERT(std::abs(toFloating(projected_v.lat).operator double()) <= 180.);

                    rectangle.min_lon =
                        std::min(rectangle.min_lon, std::min(projected_u.lon, projected_v.lon));
                    rectangle.max_lon =
                        std::max(rectangle.max_lon, std::max(projected_u.lon, projected_v.lon));

                    rectangle.min_lat =
                        std::min(rectangle.min_lat, std::min(projected_u.lat, projected_v.lat));
                    rectangle.max_lat =
                        std::max(rectangle.max_lat, std::max(projected_u.lat, projected_v.lat));

                    BOOST_ASSERT(rectangle.IsValid());
                }

                pbrtree::Rectangle *pb_rect = pb_leaf->mutable_minimum_bounding_rectangle();
                pb_rect->set_max_lat(int32_t(current_leaf.minimum_bounding_rectangle.max_lat));
                pb_rect->set_max_lon(int32_t(current_leaf.minimum_bounding_rectangle.max_lon));
                pb_rect->set_min_lat(int32_t(current_leaf.minimum_bounding_rectangle.min_lat));
                pb_rect->set_min_lon(int32_t(current_leaf.minimum_bounding_rectangle.min_lon));

                // append the leaf node to the current tree node
                current_node.child_count += 1;
                current_node.children[leaf_index] =
                    TreeIndex{node_index * BRANCHING_FACTOR + leaf_index, true};
                current_node.minimum_bounding_rectangle.MergeBoundingBoxes(
                    current_leaf.minimum_bounding_rectangle);


                // write leaf_node to leaf node file
                leaf_node_file.write((char *)&current_leaf, sizeof(current_leaf));
            }

            tree_nodes_in_level.emplace_back(current_node);
        }
        leaf_node_file.flush();
        leaf_node_file.close();

        util::SimpleLogger().Write(logWARNING) << "rtree input vector count: " << input_wrapper_vector.size() << "\n"
                                               << "      leaf node count: "  << leaf_count << "\n"
                                               << "      tree node count: "  << tree_nodes_in_level.size();


        std::fstream pb_leaves_out("1.rtree.leaves.pb", std::ios::out | std::ios::binary);
        pb_leaves.SerializeToOstream(&pb_leaves_out);

        std::uint32_t processing_level = 0;
        while (1 < tree_nodes_in_level.size())
        {
            std::vector<TreeNode> tree_nodes_in_next_level;
            std::uint32_t processed_tree_nodes_in_level = 0;
            while (processed_tree_nodes_in_level < tree_nodes_in_level.size())
            {
                TreeNode parent_node;
                // pack BRANCHING_FACTOR elements into tree_nodes each
                for (std::uint32_t current_child_node_index = 0;
                     current_child_node_index < BRANCHING_FACTOR;
                     ++current_child_node_index)
                {
                    if (processed_tree_nodes_in_level < tree_nodes_in_level.size())
                    {
                        TreeNode &current_child_node =
                            tree_nodes_in_level[processed_tree_nodes_in_level];
                        // add tree node to parent entry
                        parent_node.children[current_child_node_index] =
                            TreeIndex{m_search_tree.size(), false};
                        m_search_tree.emplace_back(current_child_node);
                        // merge MBRs
                        parent_node.minimum_bounding_rectangle.MergeBoundingBoxes(
                            current_child_node.minimum_bounding_rectangle);
                        // increase counters
                        ++parent_node.child_count;
                        ++processed_tree_nodes_in_level;
                    }
                }
                tree_nodes_in_next_level.emplace_back(parent_node);
            }
            tree_nodes_in_level.swap(tree_nodes_in_next_level);
            ++processing_level;
        }
        BOOST_ASSERT_MSG(tree_nodes_in_level.size() == 1, "tree broken, more than one root node");
        // last remaining entry is the root node, store it
        m_search_tree.emplace_back(tree_nodes_in_level[0]);

        util::SimpleLogger().Write(logWARNING) << "rtree height: " << processing_level;
        const TreeNode &_root = tree_nodes_in_level[0];
        printRectangle(_root.minimum_bounding_rectangle);
        for (const TreeIndex _idx : _root.children) {
            const TreeNode &_child = m_search_tree[_idx.index];
            printRectangle(_child.minimum_bounding_rectangle);
        }

        // reverse and renumber tree to have root at index 0
        std::reverse(m_search_tree.begin(), m_search_tree.end());

        std::uint32_t search_tree_size = m_search_tree.size();
        tbb::parallel_for(
            tbb::blocked_range<std::uint32_t>(0, search_tree_size),
            [this, &search_tree_size](const tbb::blocked_range<std::uint32_t> &range) {
                for (std::uint32_t i = range.begin(), end = range.end(); i != end; ++i)
                {
                    TreeNode &current_tree_node = this->m_search_tree[i];
                    for (std::uint32_t j = 0; j < current_tree_node.child_count; ++j)
                    {
                        if (!current_tree_node.children[j].is_leaf)
                        {
                            const std::uint32_t old_id = current_tree_node.children[j].index;
                            const std::uint32_t new_id = search_tree_size - old_id - 1;
                            current_tree_node.children[j].index = new_id;
                        }
                    }
                }
            });

        // open tree file
        boost::filesystem::ofstream tree_node_file(tree_node_filename, std::ios::binary);

        std::uint32_t size_of_tree = m_search_tree.size();
        BOOST_ASSERT_MSG(0 < size_of_tree, "tree empty");
        tree_node_file.write((char *)&size_of_tree, sizeof(std::uint32_t));
        tree_node_file.write((char *)&m_search_tree[0], sizeof(TreeNode) * size_of_tree);

        MapLeafNodesFile(leaf_node_filename);
    }

    explicit StaticRTree(const boost::filesystem::path &node_file,
                         const boost::filesystem::path &leaf_file,
                         const CoordinateListT &coordinate_list)
        : m_coordinate_list(coordinate_list)
    {
        // open tree node file and load into RAM.
        if (!boost::filesystem::exists(node_file))
        {
            throw exception("ram index file does not exist");
        }
        if (boost::filesystem::file_size(node_file) == 0)
        {
            throw exception("ram index file is empty");
        }
        boost::filesystem::ifstream tree_node_file(node_file, std::ios::binary);

        std::uint32_t tree_size = 0;
        tree_node_file.read((char *)&tree_size, sizeof(std::uint32_t));

        m_search_tree.resize(tree_size);
        if (tree_size > 0)
        {
            tree_node_file.read((char *)&m_search_tree[0], sizeof(TreeNode) * tree_size);
        }

        MapLeafNodesFile(leaf_file);
    }

    explicit StaticRTree(TreeNode *tree_node_ptr,
                         const uint64_t number_of_nodes,
                         const boost::filesystem::path &leaf_file,
                         const CoordinateListT &coordinate_list)
        : m_search_tree(tree_node_ptr, number_of_nodes), m_coordinate_list(coordinate_list)
    {
        MapLeafNodesFile(leaf_file);
    }

    void MapLeafNodesFile(const boost::filesystem::path &leaf_file)
    {
        // open leaf node file and return a pointer to the mapped leaves data
        try
        {
            m_leaves_region.open(leaf_file);
            std::size_t num_leaves = m_leaves_region.size() / sizeof(LeafNode);
            m_leaves.reset(reinterpret_cast<const LeafNode *>(m_leaves_region.data()), num_leaves);
        }
        catch (const std::exception &exc)
        {
            throw exception(boost::str(boost::format("Leaf file %1% mapping failed: %2%") %
                                       leaf_file % exc.what()));
        }
    }

    /* Returns all features inside the bounding box.
       Rectangle needs to be projected!*/
    std::vector<EdgeDataT> SearchInBox(const Rectangle &search_rectangle) const
    {
        const Rectangle projected_rectangle{
            search_rectangle.min_lon,
            search_rectangle.max_lon,
            toFixed(FloatLatitude{
                web_mercator::latToY(toFloating(FixedLatitude(search_rectangle.min_lat)))}),
            toFixed(FloatLatitude{
                web_mercator::latToY(toFloating(FixedLatitude(search_rectangle.max_lat)))})};
        std::vector<EdgeDataT> results;

        std::queue<TreeIndex> traversal_queue;
        traversal_queue.push(TreeIndex{});

        while (!traversal_queue.empty())
        {
            auto const current_tree_index = traversal_queue.front();
            traversal_queue.pop();

            if (current_tree_index.is_leaf)
            {
                const LeafNode &current_leaf_node = m_leaves[current_tree_index.index];

                for (const auto i : irange(0u, current_leaf_node.object_count))
                {
                    const auto &current_edge = current_leaf_node.objects[i];

                    // we don't need to project the coordinates here,
                    // because we use the unprojected rectangle to test against
                    const Rectangle bbox{std::min(m_coordinate_list[current_edge.u].lon,
                                                  m_coordinate_list[current_edge.v].lon),
                                         std::max(m_coordinate_list[current_edge.u].lon,
                                                  m_coordinate_list[current_edge.v].lon),
                                         std::min(m_coordinate_list[current_edge.u].lat,
                                                  m_coordinate_list[current_edge.v].lat),
                                         std::max(m_coordinate_list[current_edge.u].lat,
                                                  m_coordinate_list[current_edge.v].lat)};

                    // use the _unprojected_ input rectangle here
                    if (bbox.Intersects(search_rectangle))
                    {
                        results.push_back(current_edge);
                    }
                }
            }
            else
            {
                const TreeNode &current_tree_node = m_search_tree[current_tree_index.index];

                // If it's a tree node, look at all children and add them
                // to the search queue if their bounding boxes intersect
                for (std::uint32_t i = 0; i < current_tree_node.child_count; ++i)
                {
                    const TreeIndex child_id = current_tree_node.children[i];
                    const auto &child_rectangle =
                        child_id.is_leaf ? m_leaves[child_id.index].minimum_bounding_rectangle
                                         : m_search_tree[child_id.index].minimum_bounding_rectangle;

                    if (child_rectangle.Intersects(projected_rectangle))
                    {
                        traversal_queue.push(child_id);
                    }
                }
            }
        }
        return results;
    }

    // Override filter and terminator for the desired behaviour.
    std::vector<EdgeDataT> Nearest(const Coordinate input_coordinate,
                                   const std::size_t max_results) const
    {
        return Nearest(input_coordinate,
                       [](const CandidateSegment &) { return std::make_pair(true, true); },
                       [max_results](const std::size_t num_results, const CandidateSegment &) {
                           return num_results >= max_results;
                       });
    }

    // Override filter and terminator for the desired behaviour.
    template <typename FilterT, typename TerminationT>
    std::vector<EdgeDataT> Nearest(const Coordinate input_coordinate,
                                   const FilterT filter,
                                   const TerminationT terminate) const
    {
        std::vector<EdgeDataT> results;
        auto projected_coordinate = web_mercator::fromWGS84(input_coordinate);
        Coordinate fixed_projected_coordinate{projected_coordinate};

        std::cout << "[input] lat: "
                  << input_coordinate.lat
                  << ", lng: " << input_coordinate.lon << std::endl;

        std::cout << "[projected] Y: "
                  << fixed_projected_coordinate.lat
                  << ", X: " << fixed_projected_coordinate.lon << std::endl;

        // initialize queue with root element
        std::priority_queue<QueryCandidate> traversal_queue;
        std::vector<QueryCandidate> &_hack = Container(traversal_queue);

        traversal_queue.push(QueryCandidate{0, TreeIndex{}});

        while (!traversal_queue.empty())
        {
            QueryCandidate current_query_node = traversal_queue.top();
            traversal_queue.pop();

//            std::cout << "[rtree] squared min distance: " << current_query_node.squared_min_dist << std::endl;

            const TreeIndex &current_tree_index = current_query_node.tree_index;
            if (!current_query_node.is_segment())
            { // current object is a tree node


//                const auto &rectangle =
//                        current_tree_index.is_leaf ? m_leaves[current_tree_index.index].minimum_bounding_rectangle
//                                         : m_search_tree[current_tree_index.index].minimum_bounding_rectangle;
//                printRectangle(rectangle);
//            std::cout << "    - projected nearest: "
//                      << int32_t(current_query_node.fixed_projected_coordinate.lat) << " "
//                      << int32_t(current_query_node.fixed_projected_coordinate.lon) << std::endl;
//            std::cout << "    - distance: " << current_query_node.squared_min_dist << std::endl;

                if (current_tree_index.is_leaf)
                {
                    ExploreLeafNode(current_tree_index,
                                    fixed_projected_coordinate,
                                    projected_coordinate,
                                    traversal_queue);
                }
                else
                {
                    ExploreTreeNode(
                        current_tree_index, fixed_projected_coordinate, traversal_queue);
                }
            }
            else
            { // current candidate is an actual road segment
                printf(" ---- heap size: %d\n", traversal_queue.size());

//                printf("============================================================\n");
//                for (int i = 0; i < _hack.size(); i++) {
//                    QueryCandidate &_c = _hack.at(i);
//                    if (_c.is_segment()) {
//                        auto _edge = m_leaves[_c.tree_index.index].objects[_c.segment_index];
//                        extractor::EdgeBasedNode _e = extractor::EdgeBasedNode(_edge);
//                        printf("%4d : %16d + %u - %u (%u %u)\n", i, _c.squared_min_dist, _e.u, _e.v, _e.forward_segment_id.id, _e.reverse_segment_id.id);
//                    } else {
//                        printf("%4d : %16d -\n", i, _c.squared_min_dist);
//                    }
//                }
//                printf("============================================================\n");


                auto edge_data =
                    m_leaves[current_tree_index.index].objects[current_query_node.segment_index];
                const auto &current_candidate =
                    CandidateSegment{current_query_node.fixed_projected_coordinate, edge_data};

                extractor::EdgeBasedNode _e = extractor::EdgeBasedNode(edge_data);
                Coordinate _cu = m_coordinate_list[_e.u];
                Coordinate _cv = m_coordinate_list[_e.v];
                FloatCoordinate _proj_u = web_mercator::fromWGS84(_cu);
                FloatCoordinate _proj_v = web_mercator::fromWGS84(_cv);
                Coordinate _fixed_proj_u = web_mercator::fromWGS84(_cu);
                Coordinate _fixed_proj_v = web_mercator::fromWGS84(_cv);
                FloatCoordinate _wgs84 = util::web_mercator::toWGS84(current_query_node.fixed_projected_coordinate);

                double _ratio_float, _ratio_fixed;
                FloatCoordinate _proj_nearest_float;
                Coordinate _proj_nearest_fixed;
                std::tie(_ratio_float, _proj_nearest_float) = util::coordinate_calculation::projectPointOnSegment(_proj_u,_proj_v,projected_coordinate);
                std::tie(_ratio_fixed, _proj_nearest_fixed) = util::coordinate_calculation::projectPointOnSegment(_fixed_proj_u,_fixed_proj_v,fixed_projected_coordinate);

                std::string _arrow;
                if (_e.forward_segment_id.enabled && _e.reverse_segment_id.enabled) {
                    _arrow = "<->";
                } else if (_e.forward_segment_id.enabled) {
                    _arrow = "<--";
                } else if (_e.reverse_segment_id.enabled) {
                    _arrow = "-->";
                } else {
                    _arrow = "???";
                }

                printf("[candidate]\n");
                printf("  - distance: %llu\n", current_query_node.squared_min_dist);
                printf("  - edge: %u %s %u (%u %u)\n", _e.u ,_arrow.c_str(), _e.v, _e.forward_segment_id.id, _e.reverse_segment_id.id);
                printf("  - latlng: (lat: %i, lng: %i) %s (lat: %i, lng: %i)\n", int32_t(_cu.lat), _cu.lon, _arrow.c_str(), _cv.lat , _cv.lon);
                printf("  - mercator(float): U(Y: %.10f, X: %.10f)  V(Y: %.10f, X: %.10f)\n", double(_proj_u.lat), double(_proj_u.lon), double(_proj_v.lat), double(_proj_v.lon));
                printf("  - mercator(fixed): U(Y: %i, X: %i)  V(Y: %i, X: %i)\n", _fixed_proj_u.lat, _fixed_proj_u.lon, _fixed_proj_v.lat, _fixed_proj_v.lon);
                printf("  - project nearest(float): (Y: %.10f, X: %.10f)\n", double(_proj_nearest_float.lat), double(_proj_nearest_float.lon));
                printf("  - project nearest(fixed): (Y: %i, X: %i)\n", _proj_nearest_fixed.lat, _proj_nearest_fixed.lon);
                printf("  - ratio(float): %.10f\n", _ratio_float);
                printf("  - ratio(fixed): %.10f\n", _ratio_fixed);


                // to allow returns of no-results if too restrictive filtering, this needs to be
                // done here even though performance would indicate that we want to stop after
                // adding the first candidate
                if (terminate(results.size(), current_candidate))
                {
                    break;
                }

                auto use_segment = filter(current_candidate);
                if (!use_segment.first && !use_segment.second)
                {
                    continue;
                }
                edge_data.forward_segment_id.enabled &= use_segment.first;
                edge_data.reverse_segment_id.enabled &= use_segment.second;

                // store phantom node in result vector
                results.push_back(std::move(edge_data));
            }
        }

        return results;
    }

  private:
    template <typename QueueT>
    void ExploreLeafNode(const TreeIndex &leaf_id,
                         const Coordinate &projected_input_coordinate_fixed,
                         const FloatCoordinate &projected_input_coordinate,
                         QueueT &traversal_queue) const
    {

        const LeafNode &current_leaf_node = m_leaves[leaf_id.index];

        printf(" ====== current_leaf_node.object_count: %d\n", current_leaf_node.object_count);

        // current object represents a block on disk
        for (const auto i : irange(0u, current_leaf_node.object_count))
        {
            _debug++;

            const auto &current_edge = current_leaf_node.objects[i];
            const auto projected_u = web_mercator::fromWGS84(m_coordinate_list[current_edge.u]);
            const auto projected_v = web_mercator::fromWGS84(m_coordinate_list[current_edge.v]);

            FloatCoordinate projected_nearest;
            std::tie(std::ignore, projected_nearest) =
                coordinate_calculation::projectPointOnSegment(
                    projected_u, projected_v, projected_input_coordinate);

            const auto squared_distance = coordinate_calculation::squaredEuclideanDistance(
                projected_input_coordinate_fixed, projected_nearest);

//            extractor::EdgeBasedNode _data = extractor::EdgeBasedNode(current_edge);
//            if (squared_distance == 3787537) {
//                printf(" ====== 3787537 (%d): %d - %d (%d - %d)\n", _debug, _data.u, _data.v, _data.forward_segment_id.id, _data.reverse_segment_id.id);
//            }

//            printRectangle(current_leaf_node.minimum_bounding_rectangle);
//            std::cout << "    - projected nearest: " << double(projected_nearest.lat) << " "
//                      << double(projected_nearest.lon) << std::endl;
//            std::cout << "    - distance: " << squared_distance << std::endl;

            // distance must be non-negative
            BOOST_ASSERT(0. <= squared_distance);
            traversal_queue.push(
                QueryCandidate{squared_distance, leaf_id, i, Coordinate{projected_nearest}});
        }
    }

    template <class QueueT>
    void ExploreTreeNode(const TreeIndex &parent_id,
                         const Coordinate &fixed_projected_input_coordinate,
                         QueueT &traversal_queue) const
    {

        const TreeNode &parent = m_search_tree[parent_id.index];

        printf(" ====== ExploreTreeNode: %d\n", parent.child_count);

        for (std::uint32_t i = 0; i < parent.child_count; ++i)
        {
            _debug++;

            const TreeIndex child_id = parent.children[i];
            const auto &child_rectangle =
                child_id.is_leaf ? m_leaves[child_id.index].minimum_bounding_rectangle
                                 : m_search_tree[child_id.index].minimum_bounding_rectangle;
            const auto squared_lower_bound_to_element =
                child_rectangle.GetMinSquaredDist(fixed_projected_input_coordinate);

            traversal_queue.push(QueryCandidate{squared_lower_bound_to_element, child_id});
        }
    }
};

//[1] "On Packing R-Trees"; I. Kamel, C. Faloutsos; 1993; DOI: 10.1145/170088.170403
//[2] "Nearest Neighbor Queries", N. Roussopulos et al; 1995; DOI: 10.1145/223784.223794
//[3] "Distance Browsing in Spatial Databases"; G. Hjaltason, H. Samet; 1999; ACM Trans. DB Sys
// Vol.24 No.2, pp.265-318
}
}

#endif // STATIC_RTREE_HPP
