/**
 * @file graph_manager.cpp
 * @author mpienkos (michal.pienkos.stud@pw.edu.pl) jkedzier (michal.pienkos.stud@pw.edu.pl)
 * @brief Implementation of graph management functions.
 * @version 0.1
 * @date 2025-01-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "plugin_interface.hpp"
#include <boost/dll/import.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace GraphManager {

/**
 * @brief Gets the data of the vertices in the graph.
 * @param g Input graph.
 * @return Map of vertex indices to their data.
 */
std::unordered_map<size_t, std::string> getVerticesData(const Graph& g) {
    std::unordered_map<size_t, std::string> data;

    auto vertex_name_map = get(boost::vertex_name, g);
    for (auto [vi, vi_end] = vertices(g); vi != vi_end; ++vi) {
        data[*vi] = vertex_name_map[*vi];
    }

    return data;
}

/**
 * @brief Gets the edges of the graph.
 * @param g Input graph.
 * @return Vector of edges represented as pairs of vertex indices.
 */
std::vector<std::pair<size_t, size_t>> getEdges(const Graph& g) {
    std::vector<std::pair<size_t, size_t>> edges_list;

    for (auto [ei, ei_end] = edges(g); ei != ei_end; ++ei) {
        int source = boost::source(*ei, g);
        int target = boost::target(*ei, g);
        edges_list.emplace_back(source, target);
    }
    return edges_list;
}

/**
 * @brief Calculates the layout of the graph using a plugin.
 * @param g Input graph.
 * @param plugin_path Path to the plugin.
 * @return Map of vertex indices to their coordinates.
 */
std::unordered_map<int, std::pair<double, double>>
calculateLayout(const Graph& g, const std::string plugin_path) {
    boost::dll::fs::path plug_path = plugin_path;
    boost::dll::shared_library lib(plug_path);

    auto create_plugin =
        lib.get<PluginInterface::MyPluginApi*()>("createPlugin");
    std::shared_ptr<PluginInterface::MyPluginApi> plugin(createPlugin());

    auto coordinates = plugin->calculateGraphCoordinates(g);

    return coordinates;
}

/**
 * @brief Loads a graph from a file.
 * @param path Path to the graph file.
 * @return Loaded graph.
 */
Graph loadGraph(const std::string path) {
    Graph g;

    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open the file!");
    }

    // Wczytaj graf z pliku GraphML

    try {
        boost::dynamic_properties dp;
        dp.property("name", get(boost::vertex_name, g));
        boost::read_graphml(file, g, dp);
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to read graph!");
    }

    return g;
}

/**
 * @brief Saves a graph to a file.
 * @param g Graph to save.
 * @param path Path to the graph file.
 * @return True if successful, false otherwise.
 */
bool saveGraph(Graph& g, const std::string path) {
    std::ofstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open the file!");
    }

    try {
        boost::dynamic_properties dp;
        dp.property("name", get(boost::vertex_name, g));
        boost::write_graphml(file, g, dp);
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to write graph!");
    }
    return true;
}

/**
 * @brief Adds a node to the graph.
 * @param g Graph to modify.
 * @param name Name of the new node.
 * @return Index of the new node.
 */
int addNode(Graph& g, const std::string& name) {
    auto v = add_vertex(g);
    auto vertex_name_map = get(boost::vertex_name, g);
    vertex_name_map[v] = name;
    return v;
}

/**
 * @brief Adds an edge to the graph.
 * @param g Graph to modify.
 * @param source Source vertex index.
 * @param target Target vertex index.
 */
void addEdge(Graph& g, size_t source, size_t target) {
    if (source >= num_vertices(g) || target >= num_vertices(g)) {
        throw std::invalid_argument("Invalid source or target node id");
    }
    boost::add_edge(source, target, g);
}

/**
 * @brief Removes a node from the graph.
 * @param g Graph to modify.
 * @param node Index of the node to remove.
 */
void removeNode(Graph& g, size_t node) {
    if (node >= num_vertices(g)) {
        throw std::invalid_argument("Invalid node id");
    }
    clear_vertex(node, g);
    remove_vertex(node, g);
}

/**
 * @brief Removes an edge from the graph.
 * @param g Graph to modify.
 * @param source Source vertex index.
 * @param target Target vertex index.
 */
void removeEdge(Graph& g, size_t source, size_t target) {
    if (source >= num_vertices(g) || target >= num_vertices(g)) {
        throw std::invalid_argument("Invalid source or target node id");
    }
    auto edge_pair = boost::edge(source, target, g);
    if (edge_pair.second) {
        boost::remove_edge(edge_pair.first, g);
    } else {
        throw std::invalid_argument("Edge does not exist");
    }
}

} // namespace GraphManager
