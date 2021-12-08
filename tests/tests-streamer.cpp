#include <iostream>
#include "../cs225/catch/catch.hpp"
#include "../streamer.h"
#include <string>
#include <vector>
#include <algorithm>


using namespace std;

vector<unsigned> friends;

TEST_CASE("Test isFriend function") {
  friends.push_back(2);
  friends.push_back(3);
  friends.push_back(4);
  Streamer s = Streamer(0, "Rob", 5000, 19, friends);
  REQUIRE(s.isFriend(2) == true);
  REQUIRE(s.isFriend(99) == false);
  REQUIRE(s.isFriend(1) == false);
}

TEST_CASE("Test getId") {
  Streamer s = Streamer(0, "Rob", 5000, 19, friends);
  REQUIRE(s.getId() == 0);
}

TEST_CASE("Test getName") {
  Streamer s = Streamer(0, "Rob", 5000, 19, friends);
  REQUIRE(s.getName() == "Rob");
}

TEST_CASE("Test getViews") {
  Streamer s = Streamer(0, "Rob", 5000, 19, friends);
  REQUIRE(s.getViews() == 5000);
}

TEST_CASE("Test getAge") {
  Streamer s = Streamer(0, "Rob", 5000, 19, friends);
  REQUIRE(s.getAge() == 19);
}

TEST_CASE("Test getFriends") {
  Streamer s = Streamer(0, "Rob", 5000, 19, friends);
  REQUIRE(s.getFriends() == friends);
}