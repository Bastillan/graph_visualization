/**
 * @file plugin_interface.hpp
 * @author mpienkos (michal.pienkos.stud@pw.edu.pl) jkedzier (michal.pienkos.stud@pw.edu.pl)
 * @brief Interface for graph calculation plugins.
 * @version 0.1
 * @date 2025-01-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>
#include <string>
#include <unordered_map>
#include <vector>

using VertexProperty = boost::property<boost::vertex_name_t, std::string>;
using EdgeProperty = boost::no_property;
using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
                                    VertexProperty, EdgeProperty>;

namespace PluginInterface {

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
    virtual std::unordered_map<int, std::pair<double, double>>
    calculateGraphCoordinates(Graph graph) = 0;

    virtual ~MyPluginApi() {}
};

} // namespace PluginInterface