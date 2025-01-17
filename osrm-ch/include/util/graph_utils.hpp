#ifndef GRAPH_UTILS_HPP
#define GRAPH_UTILS_HPP

#include "util/typedefs.hpp"

#include <boost/assert.hpp>
#include <vector>

namespace osrm
{
namespace util
{

/// This function checks if the graph (consisting of directed edges) is undirected
template <typename GraphT> bool isUndirectedGraph(const GraphT &graph)
{
    for (auto source = 0u; source < graph.GetNumberOfNodes(); ++source)
    {
        for (auto edge = graph.BeginEdges(source); edge < graph.EndEdges(source); ++edge)
        {
            const auto &data = graph.GetEdgeData(edge);

            auto target = graph.GetTarget(edge);
            BOOST_ASSERT(target != SPECIAL_NODEID);

            bool found_reverse = false;
            for (auto rev_edge = graph.BeginEdges(target); rev_edge < graph.EndEdges(target);
                 ++rev_edge)
            {
                auto rev_target = graph.GetTarget(rev_edge);
                BOOST_ASSERT(rev_target != SPECIAL_NODEID);

                if (rev_target != source)
                {
                    continue;
                }

                BOOST_ASSERT_MSG(!found_reverse, "Found more than one reverse edge");
                found_reverse = true;
            }

            if (!found_reverse)
            {
                return false;
            }
        }
    }

    return true;
}

/// Since DynamicGraph assumes directed edges we have to make sure we transformed
/// the compressed edge format into single directed edges. We do this to make sure
/// every node also knows its incoming edges, not only its outgoing edges and use the reversed=true
/// flag to indicate which is which.
///
/// We do the transformation in the following way:
///
/// if the edge (a, b) is split:
///   1. this edge must be in only one direction, so its a --> b
///   2. there must be another directed edge b --> a somewhere in the data
/// if the edge (a, b) is not split:
///   1. this edge be on of a --> b od a <-> b
///      (a <-- b gets reducted to b --> a)
///   2. a --> b will be transformed to a --> b and b <-- a
///   3. a <-> b will be transformed to a --> b and b --> a
template <typename OutputEdgeT, typename InputEdgeT, typename FunctorT>
std::vector<OutputEdgeT> directedEdgesFromCompressed(const std::vector<InputEdgeT> &input_edge_list,
                                                     FunctorT copy_data)
{
    std::vector<OutputEdgeT> output_edge_list;

    int split_to_print = 10;
    int split_num = 0;

    OutputEdgeT edge;
    for (const auto &input_edge : input_edge_list)
    {
        // edges that are not forward get converted by flipping the end points
        BOOST_ASSERT(input_edge.forward);

        edge.source = input_edge.source;
        edge.target = input_edge.target;
        edge.data.reversed = false;

        BOOST_ASSERT(edge.source != edge.target);

        copy_data(edge, input_edge);

        output_edge_list.push_back(edge);

        // debug
        if (input_edge.is_split) {
            split_num++;
            if (split_num < split_to_print) {
                printf(" - split edge: %d -> %d\n", edge.source, edge.target);
            }
        }

        if (!input_edge.is_split)
        {
            std::swap(edge.source, edge.target);
            edge.data.reversed = !input_edge.backward;
            output_edge_list.push_back(edge);
        }
    }

    printf(" - split total: %d\n", split_num);

    return output_edge_list;
}
}
}

#endif
