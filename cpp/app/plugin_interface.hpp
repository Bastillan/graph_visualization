/**
 * @file plugin_interface.hpp
 * @brief Interface for graph calculation plugins.
 */

#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>
#include <string>
#include <unordered_map>
#include <vector>

using VertexProperty = boost::property<boost::vertex_name_t, std::string>;
using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
                                    VertexProperty>;

namespace PluginInterface {

/**
 * @class MyPluginApi
 * @brief Abstract class for graph calculation plugins.
 */
class BOOST_SYMBOL_VISIBLE MyPluginApi {
  public:
    /**
     * @brief Returns the name of the plugin.
     * @return Plugin name.
     */
    virtual std::string name() const = 0;

    /**
     * @brief Calculates y = a * x + b.
     * @param x Input value.
     * @param a Slope.
     * @param b Intercept.
     * @return Calculated y value.
     */
    virtual float y(float x, float a, float b) = 0;

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