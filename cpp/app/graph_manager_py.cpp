/**
 * @file plugin_manager.cpp
 * @author mpienkos (michal.pienkos.stud@pw.edu.pl) jkedzier (michal.pienkos.stud@pw.edu.pl)
 * @brief Python bindings for graph management functions.
 * @version 0.1
 * @date 2025-01-20
 * 
 * @copyright Copyright (c) 2025
 * 
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