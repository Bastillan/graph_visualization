cmake_minimum_required(VERSION 3.23)
project(graph_viewer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -pedantic -Werror -Wno-uninitialized)

add_subdirectory(app)

enable_testing()
add_subdirectory(tests)
