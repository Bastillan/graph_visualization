/**
 * @file graph_manager_py.cpp
 * @brief Python bindings for graph management functions.
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "graph_manager.hpp"

namespace py = pybind11;
using namespace GraphManager;

/**
 * @brief Python module for graph management.
 */
PYBIND11_MODULE(graphs, handle) {
    handle.doc() = "This is the module docs.";

    py::class_<Graph>(handle, "Graph")
        .def(py::init<>())
        .def("getVerticesData", &getVerticesData)
        .def("getEdges", &getEdges)
        .def("addNode", &addNode)
        .def("addEdge", &addEdge)
        .def("removeNode", &removeNode)
        .def("removeEdge", &removeEdge);

    handle.def("loadGraph", &loadGraph);
    handle.def("saveGraph", &saveGraph);
    handle.def("calculateLayout", &calculateLayout);
}