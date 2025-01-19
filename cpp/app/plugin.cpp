#include <iostream>
#include <boost/config.hpp> // for BOOST_SYMBOL_EXPORT
#include <boost/graph/graphml.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <vector>
#include <map>
#include "PluginInterface.hpp"

using VertexProperty = boost::property<boost::vertex_name_t, std::string>;

using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, VertexProperty>;

namespace my_namespace {

    class graph_calculate : public my_plugin_api {
    public:
        graph_calculate() {}

        std::string name() const {
            return "Graph calculations";
        }

        float y(float x, float a, float b) {
            return a * x + b;
        }

        std::unordered_map<int, std::pair<double, double>> calculate_graph_coordinates(Graph graph) {
            using namespace boost;
            size_t num_vertices = boost::num_vertices(graph);
            int size = sqrt(num_vertices) + 1;
            std::unordered_map<int, std::pair<double, double>> coordinates;

            int i = 0;
            auto [v_begin, v_end] = vertices(graph);
            for (auto v_it = v_begin; v_it != v_end; ++v_it) {
                coordinates[i] = {std::make_pair(i % size, i / size)};
                ++i;
            }

            return coordinates;
        }

        ~graph_calculate() {}
    };

    // Exporting `my_namespace::plugin` variable with alias name `plugin`
    // (Has the same effect as `BOOST_DLL_ALIAS(my_namespace::plugin, plugin)`)
    extern "C" BOOST_SYMBOL_EXPORT my_plugin_api* create_plugin() {
        return new graph_calculate();
    }

} // namespace my_namespace