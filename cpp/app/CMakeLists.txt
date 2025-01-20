project(graphs)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 REQUIRED)
find_package(Boost REQUIRED)

set(CMAKE_CXX_CLANG_TIDY)

add_library(graphs_core STATIC graph_manager.cpp)
target_link_libraries(graphs_core PRIVATE Boost::filesystem Boost::system Boost::graph)

pybind11_add_module(graphs graph_manager_py.cpp)
target_link_libraries(graphs PRIVATE graphs_core Boost::system Boost::graph)
set_target_properties(graphs PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../python)

add_subdirectory(plugins)
