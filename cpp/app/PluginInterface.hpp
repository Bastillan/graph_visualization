#include <boost/config.hpp>
#include <string>
#include <boost/graph/graphml.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <vector>
#include <map>

using VertexProperty = boost::property<boost::vertex_name_t, std::string>;

using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, VertexProperty>;

class BOOST_SYMBOL_VISIBLE my_plugin_api{
public:
   virtual std::string name() const = 0;
   virtual float y(float x, float a, float b) = 0;
   virtual std::unordered_map<int, std::pair<double, double>> calculate_graph_coordinates(Graph graph) = 0;
   virtual ~my_plugin_api() {}
};