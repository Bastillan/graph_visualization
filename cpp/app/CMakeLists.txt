project(calculations)

set(PYBIND_FINDPYTHON ON)
find_package(pybind11 REQUIRED)
find_package(Boost REQUIRED)

add_subdirectory(plugins)
add_executable(main_app PluginManager.cpp)
target_include_directories(main_app PRIVATE ${CMAKE_SOURCE_DIR}/plugins)
target_link_libraries(main_app PRIVATE Boost)

add_library(calculations_core STATIC math.cpp)
target_link_libraries(calculations_core PRIVATE Boost::boost)

pybind11_add_module(calculations math_py.cpp)
target_link_libraries(calculations PRIVATE calculations_core)

set_target_properties(calculations PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../python)