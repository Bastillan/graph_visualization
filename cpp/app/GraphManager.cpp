/**
 * @file math.cpp
 * @author mpienkos (michal.pienkos.stud@pw.edu.pl) jkedzier (jedrzej.kedzierski.stud@pw.edu.pl)
 * @brief Module with basic math operations
 * @version 0.1
 * @date 2024-12-04
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <boost/dll/import.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <memory>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "PluginInterface.hpp"
#include "math.hpp"

/**
 * @brief Implements addition
 *
 * @param arg1
 * @param arg2
 * @return float
 */

using VertexProperty = boost::property<boost::vertex_name_t, std::string>;

using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, VertexProperty>;

std::unordered_map<int, std::string> getVerticesData(const Graph& g) {
    std::unordered_map<int, std::string> data;

    auto vertex_name_map = get(boost::vertex_name, g);
    for (auto [vi, vi_end] = vertices(g); vi != vi_end; ++vi) {
        data[*vi] = vertex_name_map[*vi];
    }

    return data;
}

std::vector<std::pair<int, int>> getEdges(const Graph& g) {
    std::vector<std::pair<int, int>> edges_list;

    for (auto [ei, ei_end] = edges(g); ei != ei_end; ++ei) {
        int source = boost::source(*ei, g);
        int target = boost::target(*ei, g);
        edges_list.emplace_back(source, target);
    }
    return edges_list;
}

std::unordered_map<int, std::pair<double, double>> calculateLayout(const Graph& g, std::string plugin_path) {
    
    //boost::dll::fs::path plugin_path = "../cpp/app/plugins/libplugin.so";
    boost::dll::fs::path plug_path = plugin_path;


    boost::dll::shared_library lib(plug_path);             // argv[1] contains path to directory with our plugin library

    auto create_plugin = lib.get<my_plugin_api*()>("create_plugin");

    std::shared_ptr<my_plugin_api> plugin(create_plugin());
    auto coordinates = plugin->calculate_graph_coordinates(g);
    
    for (const auto& entry : coordinates) {
        int key = entry.first;  // Klucz
        double x = entry.second.first;  // Pierwsza wartość pary
        double y = entry.second.second; // Druga wartość pary

        std::cout << "Key: " << key << ", Value: (" << x << ", " << y << ")" << std::endl;
    }

    return coordinates;
}

Graph loadGraph(std::string path) {
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
    } catch (const std::exception &e) {
        std::cerr << "Błąd podczas wczytywania grafu: " << e.what() << std::endl;
        return 1;
    }

    // Wyświetlenie liczby wierzchołków i krawędzi
    

    auto vertex_name_map = get(boost::vertex_name, g);
    for (auto [vi, vi_end] = vertices(g); vi != vi_end; ++vi) {
        std::cout << "Vertex " << *vi << ": name = " << vertex_name_map[*vi] << std::endl;
    }

    return g;
}



//To do
//- dane w load graph
//- calculate positions

