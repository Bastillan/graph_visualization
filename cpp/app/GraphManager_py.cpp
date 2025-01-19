#include <pybind11/pybind11.h>

#include "GraphManager.hpp"

namespace py = pybind11;

PYBIND11_MODULE(graphs, handle) {
    handle.doc() = "This is the module docs.";

    py::class_<Graph>(handle, "Graph")
        .def(py::init<>())
        .def("getData", &getGraphData);
    
    handle.def("loadGraph", &loadGraph);
    handle.def("calculateLayout", &calculateLayout);
}