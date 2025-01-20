project(tests)

find_package(Catch2 REQUIRED)

find_package(Boost REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/app)

add_executable(unit_tests tests.cpp)

target_link_libraries(unit_tests PRIVATE graphs_core Catch2::Catch2WithMain Boost::filesystem Boost::system Boost::graph)

include(CTest)
include(Catch)
catch_discover_tests(unit_tests)