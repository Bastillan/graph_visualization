cmake_minimum_required(VERSION 3.2)
project(graph_viewer)
add_subdirectory(pybind11)
pybind11_add_module(calculations math.cpp)