#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include "../CSVParser.h"
#include "../cs225/catch/catch.hpp"
#include "../streamer.h"

using namespace std;

TEST_CASE("Creating Streamer Object") {
  CSVParser parser;
  string test = "0,73045350,1459,False,9528,False,2299,CaptainTeabeard";
  Streamer streamer;
  streamer = parser.createStreamer(test);
  REQUIRE(streamer.getId() == 2299);
  REQUIRE(streamer.getName().compare("CaptainTeabeard") == 0);
}

TEST_CASE("Testing file input") {
  ifstream input("data/test_data_friends.csv");
  string line = "";
  int count = 0;
  while (getline(input, line, '\n')) {
    REQUIRE(line.compare("529,2299") == 0);
    break;
  }
}

TEST_CASE("Parsing Friends File - Accessing File") {
  CSVParser parser;
  parser.parseFriends("data/test_data_friends.csv");
  map<unsigned, vector<unsigned>> friendsMap;
  friendsMap = parser.getFriendsMap();

  REQUIRE(friendsMap.size() != 0);
}

TEST_CASE("Parsing Friends File - Correct # Elements in Each Vector") {
  CSVParser parser;
  parser.parseFriends("data/test_data_friends.csv");
  map<unsigned, vector<unsigned>> friendsMap;
  friendsMap = parser.getFriendsMap();

  REQUIRE(friendsMap.at(2299).size() == 7);
  REQUIRE(friendsMap.at(6019).size() == 1);
  REQUIRE(friendsMap.at(397).size() == 9);
  REQUIRE(friendsMap.at(4470).size() == 9);
}

TEST_CASE("Parsing Friends File - Correct Elements in Vector") {
  CSVParser parser;
  parser.parseFriends("data/test_data_friends.csv");
  map<unsigned, vector<unsigned>> friendsMap;
  friendsMap = parser.getFriendsMap();
  REQUIRE(friendsMap.at(907)[0] == 1434);
  REQUIRE(friendsMap.at(5428)[0] == 4470);
  REQUIRE(friendsMap.at(2299)[1] == 1773);
}

TEST_CASE("Find Friends Helper") {
  CSVParser parser;
  parser.parseFriends("data/test_data_friends.csv");
  map<unsigned, vector<unsigned>> friendsMap;
  friendsMap = parser.getFriendsMap();

  vector<unsigned> friends = parser.findFriendsHelper(2299);
  vector<unsigned> check{529, 1773, 3285, 5591, 2588, 3387, 5945};

  for (size_t i = 0; i < friends.size(); i++) {
    REQUIRE(friends[i] == check[i]);
  }
}

TEST_CASE("Test parseFile") {
  CSVParser parser;
  vector<Streamer> output;
  output = parser.parseFile("data/test_data_streamer_info.csv",
                            "data/test_data_friends.csv");

  vector<string> real_names{"CaptainTeabeard",    "AwakenedOne",
                            "CharlotteSomething", "Mizumomo",
                            "onewithtehforce",    "Aletdownofstate",
                            "SkittlesRandom",     "ShadowScissors_",
                            "lemonlimepickle",    "S1MPAGG"};

  for (size_t i = 0; i < real_names.size(); i++) {
    REQUIRE(output[i].getName() == real_names[i]);
  }

  vector<unsigned> check{529, 1773, 3285, 5591, 2588, 3387, 5945};
  cout << "check" << endl;
  REQUIRE(output[0].getFriends().size() == 7);
  REQUIRE(output[1].getFriends().size() == 19);
  REQUIRE(output[2].getFriends().size() == 9);
  REQUIRE(output[3].getFriends().size() == 3);

  REQUIRE(output[1].getId() == 153);
  REQUIRE(output[2].getAge() == 411);
}
