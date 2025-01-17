#include "extractor/compressed_edge_container.hpp"
#include "util/simple_logger.hpp"

#include <boost/assert.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include <limits>
#include <string>

#include <iostream>

#include "../protobuf/node-based-graph.pb.h"

namespace osrm
{
namespace extractor
{

CompressedEdgeContainer::CompressedEdgeContainer()
{
    m_free_list.reserve(100);
    IncreaseFreeList();
}

void CompressedEdgeContainer::IncreaseFreeList()
{
    m_compressed_geometries.resize(m_compressed_geometries.size() + 100);
    for (unsigned i = 100; i > 0; --i)
    {
        m_free_list.emplace_back(free_list_maximum);
        ++free_list_maximum;
    }
}

bool CompressedEdgeContainer::HasEntryForID(const EdgeID edge_id) const
{
    auto iter = m_edge_id_to_list_index_map.find(edge_id);
    return iter != m_edge_id_to_list_index_map.end();
}

unsigned CompressedEdgeContainer::GetPositionForID(const EdgeID edge_id) const
{
    auto map_iterator = m_edge_id_to_list_index_map.find(edge_id);
    BOOST_ASSERT(map_iterator != m_edge_id_to_list_index_map.end());
    BOOST_ASSERT(map_iterator->second < m_compressed_geometries.size());
    return map_iterator->second;
}

void CompressedEdgeContainer::SerializeInternalVector(const std::string &path) const
{

    boost::filesystem::fstream geometry_out_stream(path, std::ios::binary | std::ios::out);
    const unsigned compressed_geometries = m_compressed_geometries.size() + 1;
    BOOST_ASSERT(std::numeric_limits<unsigned>::max() != compressed_geometries);
    geometry_out_stream.write((char *)&compressed_geometries, sizeof(unsigned));

    pbnbg::CompressedContainer pb_cc;


    // write indices array
    unsigned prefix_sum_of_list_indices = 0;
    for (const auto &elem : m_compressed_geometries)
    {
        geometry_out_stream.write((char *)&prefix_sum_of_list_indices, sizeof(unsigned));

        const std::vector<CompressedEdge> &current_vector = elem;
        const unsigned unpacked_size = current_vector.size();
        BOOST_ASSERT(std::numeric_limits<unsigned>::max() != unpacked_size);
        prefix_sum_of_list_indices += unpacked_size;
    }
    // sentinel element
    geometry_out_stream.write((char *)&prefix_sum_of_list_indices, sizeof(unsigned));

    // number of geometry entries to follow, it is the (inclusive) prefix sum
    geometry_out_stream.write((char *)&prefix_sum_of_list_indices, sizeof(unsigned));

    unsigned control_sum = 0;
    // write compressed geometries
    for (auto &elem : m_compressed_geometries)
    {
        const std::vector<CompressedEdge> &current_vector = elem;
        const unsigned unpacked_size = current_vector.size();
        control_sum += unpacked_size;
        BOOST_ASSERT(std::numeric_limits<unsigned>::max() != unpacked_size);

        pbnbg::EdgeBucket *pb_bucket = pb_cc.add_geometries();

        for (const auto &current_node : current_vector)
        {
            geometry_out_stream.write((char *)&(current_node), sizeof(CompressedEdge));

            pbnbg::CompressedEdge *pb_edge = pb_bucket->add_edges();
            pb_edge->set_node_id(current_node.node_id);
            pb_edge->set_weight(current_node.weight);
        }
    }

    std::fstream pb_out("1.nbg.compressed.pb",std::ios::out|std::ios::binary);
    pb_cc.SerializeToOstream(&pb_out);

    BOOST_ASSERT(control_sum == prefix_sum_of_list_indices);
}

// Adds info for a compressed edge to the container.   edge_id_2
// has been removed from the graph, so we have to save These edges/nodes
// have already been trimmed from the graph, this function just stores
// the original data for unpacking later.
//
//     edge_id_1               edge_id_2
//   ----------> via_node_id -----------> target_node_id
//     weight_1                weight_2
void CompressedEdgeContainer::CompressEdge(const EdgeID edge_id_1,
                                           const EdgeID edge_id_2,
                                           const NodeID via_node_id,
                                           const NodeID target_node_id,
                                           const EdgeWeight weight1,
                                           const EdgeWeight weight2)
{
    // remove super-trivial geometries
    BOOST_ASSERT(SPECIAL_EDGEID != edge_id_1);
    BOOST_ASSERT(SPECIAL_EDGEID != edge_id_2);
    BOOST_ASSERT(SPECIAL_NODEID != via_node_id);
    BOOST_ASSERT(SPECIAL_NODEID != target_node_id);
    BOOST_ASSERT(INVALID_EDGE_WEIGHT != weight1);
    BOOST_ASSERT(INVALID_EDGE_WEIGHT != weight2);

    // append list of removed edge_id plus via node to surviving edge id:
    // <surv_1, .. , surv_n, via_node_id, rem_1, .. rem_n
    //
    // General scheme:
    // 1. append via node id to list of edge_id_1
    // 2. find list for edge_id_2, if yes add all elements and delete it

    // Add via node id. List is created if it does not exist
    if (!HasEntryForID(edge_id_1))
    {
        // create a new entry in the map
        if (0 == m_free_list.size())
        {
            // make sure there is a place to put the entries
            IncreaseFreeList();
        }
        BOOST_ASSERT(!m_free_list.empty());
        m_edge_id_to_list_index_map[edge_id_1] = m_free_list.back();
        m_free_list.pop_back();
    }

    // find bucket index
    const auto iter = m_edge_id_to_list_index_map.find(edge_id_1);
    BOOST_ASSERT(iter != m_edge_id_to_list_index_map.end());
    const unsigned edge_bucket_id1 = iter->second;
    BOOST_ASSERT(edge_bucket_id1 == GetPositionForID(edge_id_1));
    BOOST_ASSERT(edge_bucket_id1 < m_compressed_geometries.size());

    std::vector<CompressedEdge> &edge_bucket_list1 = m_compressed_geometries[edge_bucket_id1];

    // note we don't save the start coordinate: it is implicitly given by edge 1
    // weight1 is the distance to the (currently) last coordinate in the bucket
    if (edge_bucket_list1.empty())
    {
        edge_bucket_list1.emplace_back(CompressedEdge{via_node_id, weight1});
    }

    BOOST_ASSERT(0 < edge_bucket_list1.size());
    BOOST_ASSERT(!edge_bucket_list1.empty());

    if (HasEntryForID(edge_id_2))
    {
        // second edge is not atomic anymore
        const unsigned list_to_remove_index = GetPositionForID(edge_id_2);
        BOOST_ASSERT(list_to_remove_index < m_compressed_geometries.size());

        std::vector<CompressedEdge> &edge_bucket_list2 =
            m_compressed_geometries[list_to_remove_index];

        // found an existing list, append it to the list of edge_id_1
        edge_bucket_list1.insert(
            edge_bucket_list1.end(), edge_bucket_list2.begin(), edge_bucket_list2.end());

        // remove the list of edge_id_2
        m_edge_id_to_list_index_map.erase(edge_id_2);
        BOOST_ASSERT(m_edge_id_to_list_index_map.end() ==
                     m_edge_id_to_list_index_map.find(edge_id_2));
        edge_bucket_list2.clear();
        BOOST_ASSERT(0 == edge_bucket_list2.size());
        m_free_list.emplace_back(list_to_remove_index);
        BOOST_ASSERT(list_to_remove_index == m_free_list.back());
    }
    else
    {
        // we are certain that the second edge is atomic.
        edge_bucket_list1.emplace_back(CompressedEdge{target_node_id, weight2});
    }
}

    unsigned long CompressedEdgeContainer::BucketNumber() {
        return m_compressed_geometries.size();
    }

void CompressedEdgeContainer::AddUncompressedEdge(const EdgeID edge_id,
                                                  const NodeID target_node_id,
                                                  const EdgeWeight weight)
{
    // remove super-trivial geometries
    BOOST_ASSERT(SPECIAL_EDGEID != edge_id);
    BOOST_ASSERT(SPECIAL_NODEID != target_node_id);
    BOOST_ASSERT(INVALID_EDGE_WEIGHT != weight);

    // Add via node id. List is created if it does not exist
    if (!HasEntryForID(edge_id))
    {
        // create a new entry in the map
        if (0 == m_free_list.size())
        {
            // make sure there is a place to put the entries
            IncreaseFreeList();
        }
        BOOST_ASSERT(!m_free_list.empty());
        m_edge_id_to_list_index_map[edge_id] = m_free_list.back();
        m_free_list.pop_back();
    }

    // find bucket index
    const auto iter = m_edge_id_to_list_index_map.find(edge_id);
    BOOST_ASSERT(iter != m_edge_id_to_list_index_map.end());
    const unsigned edge_bucket_id = iter->second;
    BOOST_ASSERT(edge_bucket_id == GetPositionForID(edge_id));
    BOOST_ASSERT(edge_bucket_id < m_compressed_geometries.size());

    std::vector<CompressedEdge> &edge_bucket_list = m_compressed_geometries[edge_bucket_id];

    // note we don't save the start coordinate: it is implicitly given by edge_id
    // weight is the distance to the (currently) last coordinate in the bucket
    // Don't re-add this if it's already in there.
    if (edge_bucket_list.empty())
    {
        edge_bucket_list.emplace_back(CompressedEdge{target_node_id, weight});
    }
}

void CompressedEdgeContainer::PrintStatistics() const
{
    const uint64_t compressed_edges = m_compressed_geometries.size();
    BOOST_ASSERT(0 == compressed_edges % 2);
    BOOST_ASSERT(m_compressed_geometries.size() + m_free_list.size() > 0);

    uint64_t compressed_geometries = 0;
    uint64_t longest_chain_length = 0;
    for (const std::vector<CompressedEdge> &current_vector : m_compressed_geometries)
    {
        compressed_geometries += current_vector.size();
        longest_chain_length = std::max(longest_chain_length, (uint64_t)current_vector.size());
    }

    util::SimpleLogger().Write()
        << "Geometry successfully removed:"
           "\n  compressed edges: "
        << compressed_edges << "\n  compressed geometries: " << compressed_geometries
        << "\n  longest chain length: " << longest_chain_length << "\n  cmpr ratio: "
        << ((float)compressed_edges / std::max(compressed_geometries, (uint64_t)1))
        << "\n  avg chain length: "
        << (float)compressed_geometries / std::max((uint64_t)1, compressed_edges);
}

const CompressedEdgeContainer::EdgeBucket &
CompressedEdgeContainer::GetBucketReference(const EdgeID edge_id) const
{
    const unsigned index = m_edge_id_to_list_index_map.at(edge_id);
    return m_compressed_geometries.at(index);
}

// Since all edges are technically in the compressed geometry container,
// regardless of whether a compressed edge actually contains multiple
// original segments, we use 'Trivial' here to describe compressed edges
// that only contain one original segment
bool CompressedEdgeContainer::IsTrivial(const EdgeID edge_id) const
{
    const auto &bucket = GetBucketReference(edge_id);
    return bucket.size() == 1;
}

NodeID CompressedEdgeContainer::GetFirstEdgeTargetID(const EdgeID edge_id) const
{
    const auto &bucket = GetBucketReference(edge_id);
    BOOST_ASSERT(bucket.size() >= 1);
    return bucket.front().node_id;
}
NodeID CompressedEdgeContainer::GetLastEdgeTargetID(const EdgeID edge_id) const
{
    const auto &bucket = GetBucketReference(edge_id);
    BOOST_ASSERT(bucket.size() >= 1);
    return bucket.back().node_id;
}
NodeID CompressedEdgeContainer::GetLastEdgeSourceID(const EdgeID edge_id) const
{
    const auto &bucket = GetBucketReference(edge_id);
    BOOST_ASSERT(bucket.size() >= 2);
    return bucket[bucket.size() - 2].node_id;
}
}
}
