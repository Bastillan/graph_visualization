#include <catch2/catch_test_macros.hpp>
#include "math.hpp"

TEST_CASE("MathTest Add", "[Math]") {
    REQUIRE(add(1, 2) == 3);
}