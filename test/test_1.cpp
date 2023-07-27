#include "catch_amalgamated.hpp"

int add(int a, int b) {
  return a + b;
}

TEST_CASE("Addition test", "[math]") {
  REQUIRE(add(1, 1) == 2);
}
