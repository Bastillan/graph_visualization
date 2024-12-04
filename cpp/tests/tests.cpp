#include <catch2/catch_test_macros.hpp>
#include "../app/math.cpp"

TEST_CASE("MathTest Add", "[Math]") {
    REQUIRE(add(1, 2) == 3);
}