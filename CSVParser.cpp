#include "CSVParser.h"
#include <algorithm>
#include <sstream>

using namespace std;

CSVParser::CSVParser() {}

vector<Streamer> CSVParser::parseFile(string filename, string filename_edges) {
  vector<Streamer> streamers;

  ifstream input_file(filename);

  string line = "";

  while (getline(input_file, line)) {
    streamers.push_back(createStreamer(line));
  }

  input_file.close();

  parseFriends(filename_edges);
  for (size_t i = 0; i < streamers.size(); i++) {
    vector<unsigned> streamer_friends = findFriendsHelper(streamers[i].getId());
    streamers[i].setFriends(streamer_friends);
  }

  return streamers;
}

Streamer CSVParser::createStreamer(const string &line) {
  // idx, twitchid, DAYS, mature, VIEWS, twitchpartner, NEWID, USERNAME

  vector<string> result;

  stringstream stream(line);

  string substr = "";

  while (getline(stream, substr, ',')) {
    result.push_back(substr);
  }

  stream.clear();

  unsigned age = stoi(result[2], nullptr, 0);

  string name = result[7];

  // this checks for the elusive \r that windows adds in addition to \n for some
  // reason >:(
  if (!name.empty() && name[name.size() - 1] == '\r') {
    name.erase(name.size() - 1);
  }
  unsigned views = stoi(result[4], nullptr, 0);
  unsigned newId = stoi(result[6], nullptr, 0);

  Streamer streamer(newId, name, views, age);

  return streamer;
}

void CSVParser::parseFriends(string filename) {
  map<unsigned, vector<unsigned>> friends;

  ifstream input(filename);

  string line = "";

  while (getline(input, line)) {
    stringstream stream(line);
    vector<string> split;
    while (stream.good()) {
      string substr;
      getline(stream, substr, ',');
      split.push_back(substr);
    }
    unsigned node1 = stoi(split[0], nullptr, 0);
    unsigned node2 = stoi(split[1], nullptr, 0);

    // will add the appropriate value to the map<unsigned, vector<unsigned>>

    if (friends.find(node1) == friends.end()) {  // not found
      vector<unsigned> v;
      v.push_back(node2);
      friends.insert({node1, v});
    } else {  // found
      friends.at(node1).push_back(node2);
    }

    if (friends.find(node2) == friends.end()) {  // not found
      vector<unsigned> v;
      v.push_back(node1);
      friends.insert({node2, v});
    } else {  // found
      friends.at(node2).push_back(node1);
    }
  }

  input.close();

  friend_to_friend_ = friends;
}

vector<unsigned> CSVParser::findFriendsHelper(unsigned id) {
  if (friend_to_friend_.find(id) == friend_to_friend_.end()) {
    return vector<unsigned>();
  } else {
    return friend_to_friend_.at(id);
  }
}

map<unsigned, vector<unsigned>> CSVParser::getFriendsMap() {
  return friend_to_friend_;
}