project(tests)

find_package(Catch2 REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/app)

add_executable(unit_tests tests.cpp)

target_link_libraries(unit_tests PRIVATE calculations_core Catch2::Catch2WithMain)

add_test(NAME runAllUnitTests COMMAND unit_tests)