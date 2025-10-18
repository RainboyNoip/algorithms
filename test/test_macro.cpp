#include "catch_amalgamated.hpp"
#include "base/macro.hpp"


TEST_CASE("Addition test", "[math]") {
  REQUIRE("2e3"_Number == 2000);
}

TEST_CASE("inf marco", "inf") {
  int a = inf;
  REQUIRE(  a == 0x3f3f3f3f);
  REQUIRE(  (char)inf == 0x3f);
  int b = 0x3f3f3f3f;
  REQUIRE( b == inf);

  int a1[10];
  // wow ,can use like this
  memset(a1,inf,sizeof(a1)); // <---- look this
  for(int i =0;i<10;i++) {
      // std::cout << std::hex<< a1[i] << std::endl;
      REQUIRE(a1[i] == 0x3f3f3f3f);
  }
}

