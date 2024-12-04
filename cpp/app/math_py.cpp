
#include <pybind11/pybind11.h>

#include "math.hpp"

namespace py = pybind11;

PYBIND11_MODULE(calculations, handle) {
    handle.doc() = "This is the module docs.";
    handle.def("add", &add);
    handle.def("sub", &sub);
    handle.def("mul", &mul);
    handle.def("div", &divide);
    handle.def("y", &y);
}