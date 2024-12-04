project(tests)

set(PYBIND_FINDPYTHON ON)
find_package(pybind11 REQUIRED)
find_package(Catch2 REQUIRED)

add_executable(unit_tests tests.cpp)
target_link_libraries(unit_tests PUBLIC Catch2::Catch2WithMain)

include(CTest)