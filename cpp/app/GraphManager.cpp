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
using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS>;

bool graph() {
    return true;
}

int load_graph(std::string path) {
    Graph g;
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Nie udało się otworzyć pliku graph.graphml!" << std::endl;
        return 1;
    }

    // Wczytaj graf z pliku GraphML
    boost::dynamic_properties dp;
    try {
        boost::read_graphml(file, g, dp);
    } catch (const std::exception &e) {
        std::cerr << "Błąd podczas wczytywania grafu: " << e.what() << std::endl;
        return 1;
    }

    // Wyświetlenie liczby wierzchołków i krawędzi
    boost::dll::fs::path plugin_path = "../cpp/app/plugins/libplugin.so";

    boost::dll::shared_library lib(plugin_path);             // argv[1] contains path to directory with our plugin library

    auto create_plugin = lib.get<my_plugin_api*()>("create_plugin");

    std::shared_ptr<my_plugin_api> plugin(create_plugin());
    auto coordinates = plugin->calculate_graph_coordinates(g);
    for (const auto& entry : coordinates) {
        int key = entry.first;  // Klucz
        const std::vector<std::pair<double, double>>& vec = entry.second;  // Wartość (wektor par)

        std::cout << "Klucz: " << key << std::endl;

        // Odczytujemy pary (double, double) w wektorze
        for (const auto& pair : vec) {
            double x = pair.first;  // Pierwsza liczba w parze (double)
            double y = pair.second; // Druga liczba w parze (double)

            std::cout << "  Para: (" << x << ", " << y << ")" << std::endl;
        }
    }

    // return plugin->y(x, a, b);
    return 0;
}

