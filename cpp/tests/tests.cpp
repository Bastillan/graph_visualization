#include <catch2/catch_test_macros.hpp>
#include "graph_manager.hpp"

TEST_CASE("LoadGraph test - Check edges", "[graph_manager]") {
    auto graph = GraphManager::loadGraph("./../../../tests/test_graphs/graph1.graphml");
    auto edges = GraphManager::getEdges(graph);

    CHECK(edges.at(0).first == 0);
    CHECK(edges.at(0).second == 2);
    CHECK(edges.at(1).first == 1);
    CHECK(edges.at(1).second == 2);
    CHECK(edges.at(2).first == 2);
    CHECK(edges.at(2).second == 3);
    CHECK(edges.at(3).first == 3);
    CHECK(edges.at(3).second == 5);
    CHECK(edges.at(4).first == 3);
    CHECK(edges.at(4).second == 4);
    CHECK(edges.at(5).first == 4);
    CHECK(edges.at(5).second == 6);
    CHECK(edges.at(6).first == 5);
    CHECK(edges.at(6).second == 7);
    CHECK(edges.at(7).first == 6);
    CHECK(edges.at(7).second == 5);
    CHECK(edges.at(8).first == 6);
    CHECK(edges.at(8).second == 8);
    CHECK(edges.at(9).first == 8);
    CHECK(edges.at(9).second == 7);
    CHECK(edges.at(10).first == 8);
    CHECK(edges.at(10).second == 9);
    CHECK(edges.at(11).first == 9);
    CHECK(edges.at(11).second == 10);
}

TEST_CASE("LoadGraph test - Check vertices data", "[graph_manager]") {
    auto graph = GraphManager::loadGraph("./../../../tests/test_graphs/graph1.graphml");
    auto verticesData = GraphManager::getVerticesData(graph);

    CHECK(verticesData[0] == "Node n0");
    CHECK(verticesData[1] == "Node n0");
    CHECK(verticesData[2] == "Node n2");
    CHECK(verticesData[3] == "Node n3");
    CHECK(verticesData[4] == "Node n4");
    CHECK(verticesData[5] == "Node n5");
    CHECK(verticesData[6] == "Node n6");
    CHECK(verticesData[7] == "Node n7");
    CHECK(verticesData[8] == "Node n8");
    CHECK(verticesData[9] == "Node n9");
    CHECK(verticesData[10] == "Node n10");
    CHECK(verticesData[11] == "1");
}

TEST_CASE("LoadGraph test - Check number of vertices", "[graph_manager]") {
    auto graph = GraphManager::loadGraph("./../../../tests/test_graphs/graph1.graphml");
    auto verticesData = GraphManager::getVerticesData(graph);

    CHECK(verticesData.size() == 12);
}

TEST_CASE("LoadGraph test - Check if vertex exists", "[graph_manager]") {
    auto graph = GraphManager::loadGraph("./../../../tests/test_graphs/graph1.graphml");
    auto verticesData = GraphManager::getVerticesData(graph);

    CHECK(verticesData.count(0) == 1);
    CHECK(verticesData.count(10) == 1);
    CHECK(verticesData.count(12) == 0);
}

TEST_CASE("LoadGraph test - Check number of edges", "[graph_manager]") {
    auto graph = GraphManager::loadGraph("./../../../tests/test_graphs/graph1.graphml");
    auto edges = GraphManager::getEdges(graph);

    CHECK(edges.size() == 12);
}

TEST_CASE("LoadGraph test - Check specific edge", "[graph_manager]") {
    auto graph = GraphManager::loadGraph("./../../../tests/test_graphs/graph1.graphml");
    auto edges = GraphManager::getEdges(graph);

    CHECK(edges.at(0).first == 0);
    CHECK(edges.at(0).second == 2);
}

TEST_CASE("LoadGraph test - Check invalid edge", "[graph_manager]") {
    auto graph = GraphManager::loadGraph("./../../../tests/test_graphs/graph1.graphml");
    auto edges = GraphManager::getEdges(graph);

    bool invalidEdge = false;
    for (const auto& edge : edges) {
        if (edge.first == 100 || edge.second == 200) {
            invalidEdge = true;
            break;
        }
    }
    CHECK(!invalidEdge);
}

TEST_CASE("LoadGraph test - Check reverse edge", "[graph_manager]") {
    auto graph = GraphManager::loadGraph("./../../../tests/test_graphs/graph1.graphml");
    auto edges = GraphManager::getEdges(graph);

    bool reverseEdgeFound = false;
    for (const auto& edge : edges) {
        if (edge.first == 6 && edge.second == 5) {
            reverseEdgeFound = true;
            break;
        }
    }
    CHECK(reverseEdgeFound);
}

TEST_CASE("LoadGraph test - Check specific vertex", "[graph_manager]") {
    auto graph = GraphManager::loadGraph("./../../../tests/test_graphs/graph1.graphml");
    auto verticesData = GraphManager::getVerticesData(graph);

    CHECK(verticesData[3] == "Node n3");
}

TEST_CASE("LoadGraph test - Check vertex with number", "[graph_manager]") {
    auto graph = GraphManager::loadGraph("./../../../tests/test_graphs/graph1.graphml");
    auto verticesData = GraphManager::getVerticesData(graph);

    CHECK(verticesData[11] == "1");
}

TEST_CASE("LoadGraph test - Check edge from node 3", "[graph_manager]") {
    auto graph = GraphManager::loadGraph("./../../../tests/test_graphs/graph1.graphml");
    auto edges = GraphManager::getEdges(graph);

    bool edgeFound = false;
    for (const auto& edge : edges) {
        if (edge.first == 3 && edge.second == 5) {
            edgeFound = true;
            break;
        }
    }
    CHECK(edgeFound);
}

TEST_CASE("LoadGraph test - Check node 0 connected to node 2", "[graph_manager]") {
    auto graph = GraphManager::loadGraph("./../../../tests/test_graphs/graph1.graphml");
    auto edges = GraphManager::getEdges(graph);

    bool connectionFound = false;
    for (const auto& edge : edges) {
        if (edge.first == 0 && edge.second == 2) {
            connectionFound = true;
            break;
        }
    }
    CHECK(connectionFound);
}

TEST_CASE("LoadGraph test - Check non-existent vertex", "[graph_manager]") {
    auto graph = GraphManager::loadGraph("./../../../tests/test_graphs/graph1.graphml");

    auto verticesData = GraphManager::getVerticesData(graph);
    CHECK(verticesData.count(100) == 0);
}

TEST_CASE("LoadGraph test - Check edge between 2 and 3", "[graph_manager]") {
    auto graph = GraphManager::loadGraph("./../../../tests/test_graphs/graph1.graphml");
    auto edges = GraphManager::getEdges(graph);

    bool edgeFound = false;
    for (const auto& edge : edges) {
        if (edge.first == 2 && edge.second == 3) {
            edgeFound = true;
            break;
        }
    }

    CHECK(edgeFound);
}

TEST_CASE("LoadGraph test - Check edge between 6 and 8", "[graph_manager]") {
    auto graph = GraphManager::loadGraph("./../../../tests/test_graphs/graph1.graphml");
    auto edges = GraphManager::getEdges(graph);

    bool edgeFound = false;
    for (const auto& edge : edges) {
        if (edge.first == 6 && edge.second == 8) {
            edgeFound = true;
            break;
        }
    }

    CHECK(edgeFound);
}

TEST_CASE("LoadGraph test - Check node 1 data", "[graph_manager]") {
    auto graph = GraphManager::loadGraph("./../../../tests/test_graphs/graph1.graphml");
    auto verticesData = GraphManager::getVerticesData(graph);

    CHECK(verticesData[1] == "Node n0");
}

TEST_CASE("LoadGraph test - Check node 2 data", "[graph_manager]") {
    auto graph = GraphManager::loadGraph("./../../../tests/test_graphs/graph1.graphml");
    auto verticesData = GraphManager::getVerticesData(graph);

    CHECK(verticesData[2] == "Node n2");
}

TEST_CASE("LoadGraph test - Check nodes with edges for graph2", "[graph_manager]") {
    auto graph = GraphManager::loadGraph("./../../../tests/test_graphs/graph2.graphml");
    auto edges = GraphManager::getEdges(graph);
    auto verticesData = GraphManager::getVerticesData(graph);

    REQUIRE(!verticesData.empty());

    bool hasEdges = false;
    for (const auto& edge : edges) {
        if (edge.first == 0 || edge.second == 0) {
            hasEdges = true;
            break;
        }
    }

    CHECK(hasEdges);

    hasEdges = false;
    for (const auto& edge : edges) {
        if (edge.first == 6 || edge.second == 6) {
            hasEdges = true;
            break;
        }
    }

    CHECK(hasEdges);
}

TEST_CASE("LoadGraph test - Check edges for graph2", "[graph_manager]") {
    auto graph = GraphManager::loadGraph("./../../../tests/test_graphs/graph2.graphml");
    auto edges = GraphManager::getEdges(graph);

    CHECK(edges.size() == 8);

    CHECK(edges.at(0).first == 0);
    CHECK(edges.at(0).second == 1);
    CHECK(edges.at(1).first == 0);
    CHECK(edges.at(1).second == 2);
    CHECK(edges.at(2).first == 2);
    CHECK(edges.at(2).second == 3);
}
