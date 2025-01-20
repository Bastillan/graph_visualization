/**
 * @file math.cpp
 * @author mpienkos (michal.pienkos.stud@pw.edu.pl) jkedzier
 * (jedrzej.kedzierski.stud@pw.edu.pl)
 * @brief Module with basic math operations
 * @version 0.1
 * @date 2024-12-04
 *
 * @copyright Copyright (c) 2024
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

/**
 * @brief Implements addition
 *
 * @param arg1
 * @param arg2
 * @return float
 */

using VertexProperty = boost::property<boost::vertex_name_t, std::string>;
using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
                                    VertexProperty>;

namespace GraphManager {

std::unordered_map<size_t, std::string> getVerticesData(const Graph& g) {
    std::unordered_map<size_t, std::string> data;

    auto vertex_name_map = get(boost::vertex_name, g);
    for (auto [vi, vi_end] = vertices(g); vi != vi_end; ++vi) {
        data[*vi] = vertex_name_map[*vi];
    }

    return data;
}

std::vector<std::pair<size_t, size_t>> getEdges(const Graph& g) {
    std::vector<std::pair<size_t, size_t>> edges_list;

    for (auto [ei, ei_end] = edges(g); ei != ei_end; ++ei) {
        int source = boost::source(*ei, g);
        int target = boost::target(*ei, g);
        edges_list.emplace_back(source, target);
    }
    return edges_list;
}

std::unordered_map<int, std::pair<double, double>>
calculateLayout(const Graph& g, const std::string plugin_path) {
    boost::dll::fs::path plug_path = plugin_path;
    boost::dll::shared_library lib(plug_path);

    auto create_plugin =
        lib.get<PluginInterface::MyPluginApi*()>("create_plugin");
    std::shared_ptr<PluginInterface::MyPluginApi> plugin(create_plugin());

    auto coordinates = plugin->calculateGraphCoordinates(g);

    return coordinates;
}

Graph loadGraph(const std::string path) {
    Graph g;

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Nie udało się otworzyć pliku graph.graphml!" << std::endl;
        return 1;
    }

    // Wczytaj graf z pliku GraphML

    try {
        boost::dynamic_properties dp;
        dp.property("name", get(boost::vertex_name, g));
        boost::read_graphml(file, g, dp);
    } catch (const std::exception& e) {
        std::cerr << "Błąd podczas wczytywania grafu: " << e.what()
                  << std::endl;
        return 1;
    }

    return g;
}

bool saveGraph(Graph& g, const std::string path) {
    std::ofstream file(path);
    if (!file.is_open()) {
        std::cerr << "Nie udało się otworzyć pliku graph.graphml!" << std::endl;
        return false;
    }

    try {
        boost::dynamic_properties dp;
        dp.property("name", get(boost::vertex_name, g));
        boost::write_graphml(file, g, dp);
    } catch (const std::exception& e) {
        std::cerr << "Błąd podczas wczytywania grafu: " << e.what()
                  << std::endl;
        return false;
    }
    return true;
}

int addNode(Graph& g, const std::string& name) {
    auto v = add_vertex(g);
    auto vertex_name_map = get(boost::vertex_name, g);
    vertex_name_map[v] = name;
    return v;
}

void addEdge(Graph& g, size_t source, size_t target) {
    if (source >= num_vertices(g) || target >= num_vertices(g)) {
        throw std::invalid_argument("Invalid source or target node id");
    }
    boost::add_edge(source, target, g);
}

void removeNode(Graph& g, size_t node) {
    if (node >= num_vertices(g)) {
        throw std::invalid_argument("Invalid node id");
    }
    clear_vertex(node, g);
    remove_vertex(node, g);
}

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
