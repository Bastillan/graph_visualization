#include <catch2/catch_test_macros.hpp>
#include "graph_manager.hpp"

TEST_CASE("LoadGraph test", "[graph_manager]") {
    auto graph = GraphManager::loadGraph("./tests/test_graphs/graph1.graphml");
    auto edges = GraphManager::getEdges(graph);
}
