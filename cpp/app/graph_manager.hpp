/**
 * @file graph_manager.hpp
 * @author mpienkos (michal.pienkos.stud@pw.edu.pl) jkedzier (michal.pienkos.stud@pw.edu.pl)
 * @brief Header file for graph management functions.
 * @version 0.1
 * @date 2025-01-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <unordered_map>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>

using VertexProperty = boost::property<boost::vertex_name_t, std::string>;
using EdgeProperty = boost::no_property;
using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
                                    VertexProperty, EdgeProperty>;

namespace GraphManager {

/**
 * @brief Loads a graph from a file.
 * @param path Path to the graph file.
 * @return Loaded graph.
 */
Graph loadGraph(const std::string path);

/**
 * @brief Saves a graph to a file.
 * @param g Graph to save.
 * @param path Path to the graph file.
 * @return True if successful, false otherwise.
 */
bool saveGraph(Graph& g, const std::string path);

/**
 * @brief Calculates the layout of the graph using a plugin.
 * @param g Input graph.
 * @param plugin_path Path to the plugin.
 * @return Map of vertex indices to their coordinates.
 */
std::unordered_map<size_t, std::pair<double, double>>
calculateLayout(const Graph& g, const std::string plugin_path);

/**
 * @brief Gets the data of the vertices in the graph.
 * @param g Input graph.
 * @return Map of vertex indices to their data.
 */
std::unordered_map<size_t, std::string> getVerticesData(const Graph& g);

/**
 * @brief Gets the edges of the graph.
 * @param g Input graph.
 * @return Vector of edges represented as pairs of vertex indices.
 */
std::vector<std::pair<size_t, size_t>> getEdges(const Graph& g);

/**
 * @brief Adds a node to the graph.
 * @param g Graph to modify.
 * @param name Name of the new node.
 * @return Index of the new node.
 */
int addNode(Graph& g, const std::string& name);

/**
 * @brief Adds an edge to the graph.
 * @param g Graph to modify.
 * @param source Source vertex index.
 * @param target Target vertex index.
 */
void addEdge(Graph& g, size_t source, size_t target);

/**
 * @brief Removes a node from the graph.
 * @param g Graph to modify.
 * @param node Index of the node to remove.
 */
void removeNode(Graph& g, size_t node);

/**
 * @brief Removes an edge from the graph.
 * @param g Graph to modify.
 * @param source Source vertex index.
 * @param target Target vertex index.
 */
void removeEdge(Graph& g, size_t source, size_t target);

} // namespace GraphManager

#endif