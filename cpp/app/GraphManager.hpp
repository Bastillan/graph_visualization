#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>

#include <boost/graph/graphml.hpp>
#include <boost/graph/adjacency_list.hpp>

using VertexProperty = boost::property<boost::vertex_name_t, std::string>;
using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, VertexProperty>;

Graph loadGraph(std::string path);
std::unordered_map<int, std::pair<double, double>> calculateLayout(const Graph& g, std::string plugin_path);
std::unordered_map<int, std::string> getVerticesData(const Graph& g);
std::vector<std::pair<int, int>> getEdges(const Graph& g);

#endif