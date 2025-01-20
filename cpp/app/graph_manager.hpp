#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <unordered_map>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>

using VertexProperty = boost::property<boost::vertex_name_t, std::string>;
using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
                                    VertexProperty>;

namespace GraphManager {

Graph loadGraph(const std::string path);
bool saveGraph(Graph& g, const std::string path);
std::unordered_map<size_t, std::pair<double, double>>
calculateLayout(const Graph& g, const std::string plugin_path);

std::unordered_map<size_t, std::string> getVerticesData(const Graph& g);
std::vector<std::pair<size_t, size_t>> getEdges(const Graph& g);
int addNode(Graph& g, const std::string& name);
void addEdge(Graph& g, size_t source, size_t target);
void removeNode(Graph& g, size_t node);
void removeEdge(Graph& g, size_t source, size_t target);

} // namespace GraphManager

#endif