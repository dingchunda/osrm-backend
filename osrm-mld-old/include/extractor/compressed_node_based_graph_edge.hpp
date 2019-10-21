#ifndef OSRM_EXTRACTOR_COMPRESSED_NODE_BASED_GRAPH_EDGE_HPP
#define OSRM_EXTRACTOR_COMPRESSED_NODE_BASED_GRAPH_EDGE_HPP

#include "util/typedefs.hpp"

namespace osrm
{
namespace extractor
{

// We encode the cnbg graph only using its topology as edge list
struct CompressedNodeBasedGraphEdge
{
    NodeID source;
    NodeID target;
};
}
}

#endif // OSRM_EXTRACTOR_COMPRESSED_NODE_BASED_GRAPH_EDGE_HPP
