#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "GraphManager.hpp"

namespace py = pybind11;

PYBIND11_MODULE(graphs, handle) {
    handle.doc() = "This is the module docs.";

    py::class_<Graph>(handle, "Graph")
        .def("getVerticesData", &getVerticesData)
        .def("getEdges", &getEdges);
    
    handle.def("loadGraph", &loadGraph);
    handle.def("calculateLayout", &calculateLayout);
}