#include "plugin_interface.hpp"
#include <boost/config.hpp> // for BOOST_SYMBOL_EXPORT
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>
#include <iostream>
#include <unordered_map>
#include <vector>

using VertexProperty = boost::property<boost::vertex_name_t, std::string>;
using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
                                    VertexProperty>;

namespace PluginGrid {

class GraphCalculate : public PluginInterface::MyPluginApi {
  public:
    GraphCalculate() {}

    std::string name() const { return "Graph calculations"; }

    float y(float x, float a, float b) { return a * x + b; }

    std::unordered_map<int, std::pair<double, double>>
    calculateGraphCoordinates(Graph graph) {
        using namespace boost;
        size_t num_vertices = boost::num_vertices(graph);
        int size = sqrt(num_vertices) + 1;
        std::unordered_map<int, std::pair<double, double>> coordinates;

        int i = 0;
        auto [v_begin, v_end] = vertices(graph);
        for (auto v_it = v_begin; v_it != v_end; ++v_it) {
            coordinates[i] = (std::make_pair(i % size, i / size));
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

} // namespace PluginGrid