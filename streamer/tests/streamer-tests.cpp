#include "../../catch/catch.hpp"
#include "../streamer.h"
#include <iostream>

using namespace std;

TEST_CASE("Sanity") {
    cout << "Streamer test sanity" << endl;
    REQUIRE(1 == 1);
}