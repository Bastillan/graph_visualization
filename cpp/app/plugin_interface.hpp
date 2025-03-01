/**
 * @file plugin_interface.hpp
 * @author mpienkos (michal.pienkos.stud@pw.edu.pl) jkedzier
 * (jedrzej.kedzierski.stud@pw.edu.pl)
 * @brief Interface for graph calculation plugins.
 * @version 0.1
 * @date 2025-01-20
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef PLUGIN_INTERFACE_HPP
#define PLUGIN_INTERFACE_HPP

#include "graph_manager.hpp"
#include <boost/config.hpp>
#include <string>
#include <unordered_map>
#include <vector>

namespace PluginInterface {

using Graph = GraphManager::Graph;

/**
 * @class MyPluginApi
 * @brief Abstract class for graph calculation plugins.
 */
class BOOST_SYMBOL_VISIBLE MyPluginApi {
  public:
    /**
     * @brief Calculates coordinates for the graph vertices.
     * @param graph Input graph.
     * @return Map of vertex indices to their coordinates.
     */
    virtual std::unordered_map<size_t, std::pair<double, double>>
    calculateGraphCoordinates(Graph graph) = 0;

    virtual ~MyPluginApi() {}
};

} // namespace PluginInterface

#endif // PLUGIN_INTERFACE_HPP
