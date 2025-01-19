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
    std::cout << "Liczba wierzchołków: " << boost::num_vertices(g) << std::endl;
    std::cout << "Liczba krawędzi: " << boost::num_edges(g) << std::endl;

    return 0;
}

