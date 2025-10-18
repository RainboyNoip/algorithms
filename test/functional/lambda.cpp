#include "functional/lambda.hpp"
#include "catch_amalgamated.hpp"
using namespace lambda;

TEST_CASE("Functional", "[lambda]") {
    int x[] = {1,2,3,4};
    REQUIRE(_1[0](x) == 1);
}
