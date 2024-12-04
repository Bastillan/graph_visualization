project(calculations)

set(PYBIND_FINDPYTHON ON)
find_package(pybind11 REQUIRED)
find_package(Boost REQUIRED)

pybind11_add_module(calculations math.cpp)
target_link_libraries(calculations PUBLIC boost::boost)

set_target_properties(calculations PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../python)