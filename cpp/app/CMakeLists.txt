project(graphs)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 REQUIRED)
find_package(Boost REQUIRED)

add_executable(main_app PluginManager.cpp)
target_link_libraries(main_app PRIVATE Boost::boost)

add_library(graphs_core STATIC math.cpp GraphManager.cpp)

add_library(plugin SHARED plugin.cpp)
target_link_libraries(plugin PRIVATE Boost::boost)

target_link_libraries(graphs_core PRIVATE Boost::filesystem Boost::system Boost::graph)
target_link_libraries(main_app PRIVATE Boost::filesystem Boost::system)

pybind11_add_module(graphs math_py.cpp GraphManager_py.cpp)
target_link_libraries(graphs PRIVATE graphs_core)

set_target_properties(graphs PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../python)
set_target_properties(plugin PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/app/plugins)