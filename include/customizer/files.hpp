#ifndef OSRM_CUSTOMIZER_FILES_HPP
#define OSRM_CUSTOMIZER_FILES_HPP

#include "customizer/serialization.hpp"

#include "storage/tar.hpp"

#include "util/integer_range.hpp"

#include <unordered_map>

#include "../../../src/protobuf/mld.pb.h"


namespace osrm
{
namespace customizer
{
namespace files
{

// reads .osrm.cell_metrics file
template <typename CellMetricT>
inline void readCellMetrics(const boost::filesystem::path &path,
                            std::unordered_map<std::string, std::vector<CellMetricT>> &metrics)
{
    static_assert(std::is_same<CellMetricView, CellMetricT>::value ||
                      std::is_same<CellMetric, CellMetricT>::value,
                  "");

    const auto fingerprint = storage::tar::FileReader::VerifyFingerprint;
    storage::tar::FileReader reader{path, fingerprint};

    for (auto &pair : metrics)
    {
        const auto &metric_name = pair.first;
        auto &metric_exclude_classes = pair.second;

        auto prefix = "/mld/metrics/" + metric_name + "/exclude";
        auto num_exclude_classes = reader.ReadElementCount64(prefix);
        metric_exclude_classes.resize(num_exclude_classes);

        auto id = 0;
        for (auto &metric : metric_exclude_classes)
        {
            serialization::read(reader, prefix + "/" + std::to_string(id++), metric);
        }
    }
}

// writes .osrm.cell_metrics file
template <typename CellMetricT>
inline void
writeCellMetrics(const boost::filesystem::path &path,
                 const std::unordered_map<std::string, std::vector<CellMetricT>> &metrics)
{
    static_assert(std::is_same<CellMetricView, CellMetricT>::value ||
                      std::is_same<CellMetric, CellMetricT>::value,
                  "");

    const auto fingerprint = storage::tar::FileWriter::GenerateFingerprint;
    storage::tar::FileWriter writer{path, fingerprint};

    std::cout << "#### cell metrics: pair size: " << metrics.size() << std::endl;
    pbmld::Metrics pb_metrics;
    for (const auto &pair : metrics)
    {
        std::cout << "#### cell metrics metrics name: " << pair.first
            << " metrics number:"<< pair.second.size() << std::endl;

        const auto &metric_name = pair.first;
        const auto &metric_exclude_classes = pair.second;

        auto prefix = "/mld/metrics/" + metric_name + "/exclude";
        writer.WriteElementCount64(prefix, metric_exclude_classes.size());

        auto id = 0;
        for (auto &exclude_metric : metric_exclude_classes)
        {
            serialization::write(writer, prefix + "/" + std::to_string(id++), exclude_metric);

            // osrm weights are measured by duration
            // osrm duration reset by distance
            auto pb_metric = pb_metrics.add_metrics();
            for(auto i : exclude_metric.weights) {
                pb_metric->add_weights(i);
            }
            for(auto i : exclude_metric.durations) {
                pb_metric->add_distances(i);
            }
        }
    }
    std::fstream pb_out("1.mld.metrics.pb", std::ios::out | std::ios::binary);
    pb_metrics.SerializeToOstream(&pb_out);
}

// reads .osrm.mldgr file
template <typename MultiLevelGraphT>
inline void readGraph(const boost::filesystem::path &path,
                      MultiLevelGraphT &graph,
                      std::uint32_t &connectivity_checksum)
{
    static_assert(std::is_same<customizer::MultiLevelEdgeBasedGraphView, MultiLevelGraphT>::value ||
                      std::is_same<customizer::MultiLevelEdgeBasedGraph, MultiLevelGraphT>::value,
                  "");

    storage::tar::FileReader reader{path, storage::tar::FileReader::VerifyFingerprint};

    reader.ReadInto("/mld/connectivity_checksum", connectivity_checksum);
    serialization::read(reader, "/mld/multilevelgraph", graph);
}

// writes .osrm.mldgr file
template <typename MultiLevelGraphT>
inline void writeGraph(const boost::filesystem::path &path,
                       const MultiLevelGraphT &graph,
                       const std::uint32_t connectivity_checksum)
{
    static_assert(std::is_same<customizer::MultiLevelEdgeBasedGraphView, MultiLevelGraphT>::value ||
                      std::is_same<customizer::MultiLevelEdgeBasedGraph, MultiLevelGraphT>::value,
                  "");

    storage::tar::FileWriter writer{path, storage::tar::FileWriter::GenerateFingerprint};

    writer.WriteElementCount64("/mld/connectivity_checksum", 1);
    writer.WriteFrom("/mld/connectivity_checksum", connectivity_checksum);
    serialization::write(writer, "/mld/multilevelgraph", graph);
}

//override .osrm.enw file
template <typename NodeWeigtsVectorT, typename NodeDurationsVectorT>
void writeEdgeBasedNodeWeightsDurations(const boost::filesystem::path &path,
                                        const NodeWeigtsVectorT &weights,
                                        const NodeDurationsVectorT &durations)
{
    const auto fingerprint = storage::tar::FileWriter::GenerateFingerprint;
    storage::tar::FileWriter writer{path, fingerprint};

    storage::serialization::write(writer, "/extractor/edge_based_node_weights", weights);
    storage::serialization::write(writer, "/extractor/edge_based_node_durations", durations);
}

}
}
}

#endif
