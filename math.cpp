#include <pybind11/pybind11.h>

namespace py = pybind11;

float add(float arg1, float arg2) {
    return arg1 + arg2;
}

PYBIND11_MODULE(calculations, handle) {
    handle.doc() = "This is the module docs.";
    handle.def("add", &add);
}