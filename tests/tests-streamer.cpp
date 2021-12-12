#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "../cs225/catch/catch.hpp"
#include "../streamer.h"

using namespace std;

vector<unsigned> friends;

TEST_CASE("Test isFriend function", "[streamer]") {
  friends.push_back(2);
  friends.push_back(3);
  friends.push_back(4);
  Streamer s = Streamer(0, "Rob", 5000, 19, friends);
  REQUIRE(s.isFriend(2) == true);
  REQUIRE(s.isFriend(99) == false);
  REQUIRE(s.isFriend(1) == false);
}

TEST_CASE("Test getId", "[streamer]") {
  Streamer s = Streamer(0, "Rob", 5000, 19, friends);
  REQUIRE(s.getId() == 0);
}

TEST_CASE("Test getName", "[streamer]") {
  Streamer s = Streamer(0, "Rob", 5000, 19, friends);
  REQUIRE(s.getName() == "Rob");
}

TEST_CASE("Test getViews", "[streamer]") {
  Streamer s = Streamer(0, "Rob", 5000, 19, friends);
  REQUIRE(s.getViews() == 5000);
}

TEST_CASE("Test getAge", "[streamer]") {
  Streamer s = Streamer(0, "Rob", 5000, 19, friends);
  REQUIRE(s.getAge() == 19);
}

TEST_CASE("Test getFriends", "[streamer]") {
  Streamer s = Streamer(0, "Rob", 5000, 19, friends);
  REQUIRE(s.getFriends() == friends);
}