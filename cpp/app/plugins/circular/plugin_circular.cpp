/**
 * @file plugin_circular.cpp
 * @author mpienkos (michal.pienkos.stud@pw.edu.pl) jkedzier (jedrzej.kedzierski.stud@pw.edu.pl)
 * @brief Plugin for circular-based graph calculations.
 * @version 0.1
 * @date 2025-01-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "plugin_interface.hpp"
#include <boost/config.hpp> // for BOOST_SYMBOL_EXPORT
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>
#include <iostream>
#include <unordered_map>
#include <vector>

namespace PluginCircular {

using Graph = PluginInterface::Graph;

/**
 * @class GraphCalculate
 * @brief Implements circular-based graph calculations.
 */
class GraphCalculate : public PluginInterface::MyPluginApi {
  public:
    GraphCalculate() {}

    /**
     * @brief Calculates circular coordinates for the graph vertices.
     * @param graph Input graph.
     * @return Map of vertex indices to their coordinates.
     */
    std::unordered_map<size_t, std::pair<double, double>>
    calculateGraphCoordinates(Graph graph) {
        using namespace boost;
        size_t num_vertices = boost::num_vertices(graph);
        std::unordered_map<size_t, std::pair<double, double>> coordinates;

        size_t i = 0;
        auto [v_begin, v_end] = vertices(graph);
        for (auto v_it = v_begin; v_it != v_end; ++v_it) {
            coordinates[i] =
                (std::make_pair(cos(2 * M_PI * i / num_vertices) + 1,
                                sin(2 * M_PI * i / num_vertices) + 1));
            ++i;
        }

        return coordinates;
    }

    ~GraphCalculate() {}
};

// Exporting `my_namespace::plugin` variable with alias name `plugin`
// (Has the same effect as `BOOST_DLL_ALIAS(my_namespace::plugin, plugin)`)
extern "C" BOOST_SYMBOL_EXPORT PluginInterface::MyPluginApi* createPlugin() {
    return new GraphCalculate();
}

} // namespace PluginCircular