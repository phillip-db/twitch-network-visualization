#include <iostream>
#include "../cs225/catch/catch.hpp"
#include "../streamer.h"

using namespace std;

TEST_CASE("Sanity") {
  cout << "Streamer test sanity" << endl;
  REQUIRE(1 == 1);
}