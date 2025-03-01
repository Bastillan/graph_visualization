#include <catch2/catch_test_macros.hpp>
#include "graph_manager.hpp"

using Graph = GraphManager::Graph;

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

TEST_CASE("LoadGraph test - Check edge exists", "[graph_manager]") {
    auto graph = GraphManager::loadGraph("./../../../tests/test_graphs/graph1.graphml");
    auto edges = GraphManager::getEdges(graph);

    bool EdgeFound = false;
    for (const auto& edge : edges) {
        if (edge.first == 6 && edge.second == 5) {
            EdgeFound = true;
            break;
        }
    }
    CHECK(EdgeFound);
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

TEST_CASE("LoadGraph test - Check edges for graph2", "[graph_manager]") {
    auto graph = GraphManager::loadGraph("./../../../tests/test_graphs/graph2.graphml");
    auto edges = GraphManager::getEdges(graph);

    CHECK(edges.size() == 8);

    CHECK(edges[0].first == 0);
    CHECK(edges[0].second == 1);

    CHECK(edges[1].first == 0);
    CHECK(edges[1].second == 2);
}

TEST_CASE("LoadGraph test - Check disconnected node for graph2", "[graph_manager]") {
    auto graph = GraphManager::loadGraph("./../../../tests/test_graphs/graph2.graphml");
    auto verticesData = GraphManager::getVerticesData(graph);
    auto edges = GraphManager::getEdges(graph);

    bool hasEdges = false;
    for (const auto& edge : edges) {
        if (edge.first == 9 || edge.second == 9) {
            hasEdges = true;
            break;
        }
    }

    CHECK(!hasEdges);
}

TEST_CASE("LoadGraph test - Check edge count for graph2", "[graph_manager]") {
    auto graph = GraphManager::loadGraph("./../../../tests/test_graphs/graph2.graphml");
    auto edges = GraphManager::getEdges(graph);

    CHECK(edges.size() == 8);
}

TEST_CASE("LoadGraph test - Check source and target for edges in graph2", "[graph_manager]") {
    auto graph = GraphManager::loadGraph("./../../../tests/test_graphs/graph2.graphml");
    auto edges = GraphManager::getEdges(graph);

    CHECK(edges[0].first == 0);
    CHECK(edges[0].second == 1);

    CHECK(edges[1].first == 0);
    CHECK(edges[1].second == 2);
}

TEST_CASE("LoadGraph test - Check multiple edges from one node for graph2", "[graph_manager]") {
    auto graph = GraphManager::loadGraph("./../../../tests/test_graphs/graph2.graphml");
    auto edges = GraphManager::getEdges(graph);

    int count = 0;
    for (const auto& edge : edges) {
        if (edge.first == 0) {
            count++;
        }
    }

    CHECK(count == 2);
}

TEST_CASE("LoadGraph test - Check correct number of vertices for graph2", "[graph_manager]") {
    auto graph = GraphManager::loadGraph("./../../../tests/test_graphs/graph2.graphml");
    auto verticesData = GraphManager::getVerticesData(graph);

    CHECK(verticesData.size() == 10);
}

TEST_CASE("LoadGraph test - Check specific node data for graph2", "[graph_manager]") {
    auto graph = GraphManager::loadGraph("./../../../tests/test_graphs/graph2.graphml");
    auto verticesData = GraphManager::getVerticesData(graph);

    CHECK(verticesData[3] == "Node 3");

    CHECK(verticesData[7] == "Node 7");
}

TEST_CASE("LoadGraph test - adding nodes and edges to graph", "[graph_manager]") {
    auto graph = Graph();
    GraphManager::addNode(graph, "n0");
    GraphManager::addNode(graph, "n1");
    GraphManager::addNode(graph, "n2");
    GraphManager::addEdge(graph, 1, 2);
    auto edges = GraphManager::getEdges(graph);

    CHECK(edges.at(0).first == 1);
    CHECK(edges.at(0).second == 2);
}

TEST_CASE("LoadGraph test - saving graph", "[graph_manager]") {
    auto graph = Graph();
    GraphManager::addNode(graph, "n0");
    GraphManager::addNode(graph, "n1");
    GraphManager::addNode(graph, "n2");
    GraphManager::addEdge(graph, 1, 2);
    GraphManager::saveGraph(graph, "./../../../tests/test_graphs/graph_test.graphml");
    auto new_graph = GraphManager::loadGraph("./../../../tests/test_graphs/graph_test.graphml");
    auto edges = GraphManager::getEdges(new_graph);
    auto nodes = GraphManager::getVerticesData(new_graph);
    
    CHECK(edges.at(0).first == 1);
    CHECK(edges.at(0).second == 2);
    CHECK(nodes[0] == "n0");
}

TEST_CASE("LoadGraph test - saving and loading a graph with multiple edges", "[graph_manager]") {
    auto graph = Graph();
    GraphManager::addNode(graph, "n0");
    GraphManager::addNode(graph, "n1");
    GraphManager::addNode(graph, "n2");
    GraphManager::addEdge(graph, 0, 1);
    GraphManager::addEdge(graph, 1, 2);
    GraphManager::saveGraph(graph, "./../../../tests/test_graphs/graph_test_2.graphml");
    auto new_graph = GraphManager::loadGraph("./../../../tests/test_graphs/graph_test_2.graphml");
    auto edges = GraphManager::getEdges(new_graph);
    auto nodes = GraphManager::getVerticesData(new_graph);
    
    CHECK(edges.at(0).first == 0);
    CHECK(edges.at(0).second == 1);
    CHECK(edges.at(1).first == 1);
    CHECK(edges.at(1).second == 2);
    CHECK(nodes[0] == "n0");
}

TEST_CASE("LoadGraph test - saving and loading an empty graph", "[graph_manager]") {
    auto graph = Graph();
    GraphManager::saveGraph(graph, "./../../../tests/test_graphs/graph_test_4.graphml");
    auto new_graph = GraphManager::loadGraph("./../../../tests/test_graphs/graph_test_4.graphml");
    auto edges = GraphManager::getEdges(new_graph);
    auto nodes = GraphManager::getVerticesData(new_graph);
    
    CHECK(edges.size() == 0);
    CHECK(nodes.size() == 0);
}

TEST_CASE("LoadGraph test - saving and loading graph with one node and self-loop", "[graph_manager]") {
    auto graph = Graph();
    GraphManager::addNode(graph, "n0");
    GraphManager::addEdge(graph, 0, 0);
    GraphManager::saveGraph(graph, "./../../../tests/test_graphs/graph_test_5.graphml");
    auto new_graph = GraphManager::loadGraph("./../../../tests/test_graphs/graph_test_5.graphml");
    auto edges = GraphManager::getEdges(new_graph);
    auto nodes = GraphManager::getVerticesData(new_graph);
    
    CHECK(edges.size() == 1);
    CHECK(edges.at(0).first == 0);
    CHECK(edges.at(0).second == 0);
    CHECK(nodes[0] == "n0");
}

TEST_CASE("LoadGraph test - saving and loading graph with multiple nodes and edges", "[graph_manager]") {
    auto graph = Graph();
    GraphManager::addNode(graph, "n0");
    GraphManager::addNode(graph, "n1");
    GraphManager::addNode(graph, "n2");
    GraphManager::addNode(graph, "n3");
    GraphManager::addEdge(graph, 0, 1);
    GraphManager::addEdge(graph, 1, 2);
    GraphManager::addEdge(graph, 2, 3);
    GraphManager::saveGraph(graph, "./../../../tests/test_graphs/graph_test_6.graphml");
    auto new_graph = GraphManager::loadGraph("./../../../tests/test_graphs/graph_test_6.graphml");
    auto edges = GraphManager::getEdges(new_graph);
    auto nodes = GraphManager::getVerticesData(new_graph);
    
    CHECK(edges.size() == 3);
    CHECK(edges.at(0).first == 0);
    CHECK(edges.at(0).second == 1);
    CHECK(edges.at(1).first == 1);
    CHECK(edges.at(1).second == 2);
    CHECK(edges.at(2).first == 2);
    CHECK(edges.at(2).second == 3);
    CHECK(nodes[3] == "n3");
}

TEST_CASE("DeleteNode test - Check node deletion", "[graph_manager]") {
    auto graph = Graph();
    GraphManager::addNode(graph, "n0");
    GraphManager::addNode(graph, "n1");
    GraphManager::addNode(graph, "n2");
    GraphManager::removeNode(graph, 1);
    auto verticesData = GraphManager::getVerticesData(graph);

    CHECK(verticesData.size() == 2);
}

TEST_CASE("DeleteEdge test - Check edge deletion", "[graph_manager]") {
    auto graph = Graph();
    GraphManager::addNode(graph, "n0");
    GraphManager::addNode(graph, "n1");
    GraphManager::addNode(graph, "n2");
    GraphManager::addEdge(graph, 0, 1);
    GraphManager::addEdge(graph, 1, 2);
    GraphManager::removeEdge(graph, 0, 1);
    auto edges = GraphManager::getEdges(graph);

    CHECK(edges.size() == 1);
    CHECK(edges.at(0).first == 1);
    CHECK(edges.at(0).second == 2);
}

TEST_CASE("DeleteNode test - Check edges after node deletion", "[graph_manager]") {
    auto graph = Graph();
    GraphManager::addNode(graph, "n0");
    GraphManager::addNode(graph, "n1");
    GraphManager::addNode(graph, "n2");
    GraphManager::addEdge(graph, 0, 1);
    GraphManager::addEdge(graph, 1, 2);
    GraphManager::removeNode(graph, 1);
    auto edges = GraphManager::getEdges(graph);

    CHECK(edges.size() == 0);
}

TEST_CASE("DeleteEdge test - Check non-existent edge deletion", "[graph_manager]") {
    auto graph = Graph();
    GraphManager::addNode(graph, "n0");
    GraphManager::addNode(graph, "n1");
    GraphManager::addNode(graph, "n2");
    GraphManager::addEdge(graph, 0, 1);
    try {
        GraphManager::removeEdge(graph, 1, 2); // Non-existent edge
    } catch (const std::exception& e) {
        CHECK(std::string(e.what()) == "Edge does not exist");
    }
    auto edges = GraphManager::getEdges(graph);

    CHECK(edges.size() == 1);
    CHECK(edges.at(0).first == 0);
    CHECK(edges.at(0).second == 1);
}

TEST_CASE("AddEdge test - Check edge addition with non-existent nodes", "[graph_manager]") {
    auto graph = Graph();
    GraphManager::addNode(graph, "n0");
    try {
        GraphManager::addEdge(graph, 0, 1); // Target node does not exist
    } catch (const std::exception& e) {
        CHECK(std::string(e.what()) == "Invalid source or target node id");
    }
    auto edges = GraphManager::getEdges(graph);

    CHECK(edges.size() == 0);
}

TEST_CASE("RemoveNode test - Check non-existent node deletion", "[graph_manager]") {
    auto graph = Graph();
    GraphManager::addNode(graph, "n0");
    try {
        GraphManager::removeNode(graph, 1); // Non-existent node
    } catch (const std::exception& e) {
        CHECK(std::string(e.what()) == "Invalid node id");
    }
    auto verticesData = GraphManager::getVerticesData(graph);

    CHECK(verticesData.size() == 1);
    CHECK(verticesData[0] == "n0");
}

TEST_CASE("RemoveEdge test - Check edge deletion with non-existent nodes", "[graph_manager]") {
    auto graph = Graph();
    GraphManager::addNode(graph, "n0");
    GraphManager::addNode(graph, "n1");
    GraphManager::addEdge(graph, 0, 1);
    try {
        GraphManager::removeEdge(graph, 0, 2); // Target node does not exist
    } catch (const std::exception& e) {
        CHECK(std::string(e.what()) == "Invalid source or target node id");
    }
    auto edges = GraphManager::getEdges(graph);

    CHECK(edges.size() == 1);
    CHECK(edges.at(0).first == 0);
    CHECK(edges.at(0).second == 1);
}

TEST_CASE("LoadGraph test - Check loading non-existent file", "[graph_manager]") {
    try {
        auto graph = GraphManager::loadGraph("./non_existent_file.graphml");
    } catch (const std::exception& e) {
        CHECK(std::string(e.what()) == "Failed to open the file!");
    }
}

TEST_CASE("SaveGraph test - Check saving to invalid path", "[graph_manager]") {
    auto graph = Graph();
    GraphManager::addNode(graph, "n0");
    try {
        GraphManager::saveGraph(graph, "/invalid_path/graph_test.graphml");
    } catch (const std::exception& e) {
        CHECK(std::string(e.what()) == "Failed to open the file!");
    }
}

