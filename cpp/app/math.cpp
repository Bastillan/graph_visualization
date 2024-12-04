/**
 * @file math.cpp
 * @author mpienkos (michal.pienkos.stud@pw.edu.pl) jkedzier (jedrzej.kedzierski.stud@pw.edu.pl)
 * @brief Module with basic math operations
 * @version 0.1
 * @date 2024-12-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <pybind11/pybind11.h>

namespace py = pybind11;

/**
 * @brief Implements addition
 * 
 * @param arg1 
 * @param arg2 
 * @return float 
 */
float add(float arg1, float arg2) {
    return arg1 + arg2;
}

float sub(float arg1, float arg2) {
    return arg1 - arg2;
}

float mul(float arg1, float arg2) {
    return arg1 * arg2;
}

float divide(float arg1, float arg2) {
    return arg1 / arg2;
}

float y(float x, float a, float b) {
    return a * x + b;
}

PYBIND11_MODULE(calculations, handle) {
    handle.doc() = "This is the module docs.";
    handle.def("add", &add);
    handle.def("sub", &sub);
    handle.def("mul", &mul);
    handle.def("div", &divide);
    handle.def("y", &y);
}