#include <pybind11/pybind11.h>

#include "GraphManager.hpp"

namespace py = pybind11;

PYBIND11_MODULE(graphs, handle) {
    handle.doc() = "This is the module docs.";
    handle.def("graph", &graph);
    handle.def("load_graph", &load_graph);
}