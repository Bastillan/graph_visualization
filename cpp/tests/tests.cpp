#include <catch2/catch_test_macros.hpp>
#include "math.hpp"

TEST_CASE("MathTest Add", "[Math]") {
    CHECK(add(1, 2) == 3);
    CHECK(add(0, 0) == 0);
    CHECK(add(-2, 2) == 0);
    CHECK(add(1000, 20000) == 21000);
}

TEST_CASE("MathTest Sub", "[Math]") {
    CHECK(sub(1, 2) == -1);
    CHECK(sub(4, 1) == 3);
    CHECK(sub(1000, 2000) == -1000);
    CHECK(sub(100, 2) == 98);
}

TEST_CASE("MathTest Mul", "[Math]") {
    CHECK(mul(1, 2) == 2);
    CHECK(mul(0, 0) == 0);
    CHECK(mul(-1, 2) == -2);
    CHECK(mul(-1, -2) == 2);
}

TEST_CASE("MathTest Divide", "[Math]") {
    CHECK(divide(1, 2) == 0.5);
    CHECK(divide(0, 2) == 0);
    CHECK(divide(-1, 2) == -0.5);
    CHECK(divide(-1, -2) == 0.5);
}

// TEST_CASE("MathTest y", "[Math]") {
//     CHECK(y(1, 1, 1) == 2);
//     CHECK(y(2, -1, 0) == -2);
//     CHECK(y(2, 10, -1) == 19);
//     CHECK(y(1, 0, 0) == 0);
// }