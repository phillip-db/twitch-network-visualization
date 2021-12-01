#include <algorithm>
#include <iostream>
#include "../../catch/catch.hpp"
#include "../graph.h"

using namespace std;

Graph g;

TEST_CASE("Test graph initialization") {
  CSVParser parser;
  vector<Streamer> output;
  output = parser.parseFile("data/test_graph_streamers.csv",
                            "data/test_graph_friends.csv");

  int numNodes = Graph::kNumNodes;

  g = Graph(output, numNodes);
  REQUIRE(g.getNumStreamers() == numNodes);
}

TEST_CASE("Test edge list with invalid id") {
  REQUIRE(g.getEdges(10000).empty());
}

TEST_CASE("Test edge list") {
  vector<unsigned> friends = g.getEdges(2299);
  vector<unsigned> check{529, 1773, 3285, 5591, 2588, 3387, 5945};
  std::sort(check.begin(), check.end());
  for (size_t i = 0; i < friends.size(); i++) {
    REQUIRE(friends[i] == check[i]);
  }
}

TEST_CASE("Test isAdjacent with invalid id") {
  REQUIRE(!g.isAdjacent(10000, 0));
}

TEST_CASE("Test isAdjacent other nodes") {
  REQUIRE(g.isAdjacent(2299, 529));
  REQUIRE(!g.isAdjacent(2299, 0));
}

TEST_CASE("Test node is not adjacent to itself") {
  REQUIRE(!g.isAdjacent(2299, 2299));
}

TEST_CASE("Test edge weight with invalid id") {
    REQUIRE(g.getEdgeWeight(10000, 0) == -1);
}

TEST_CASE("Test edge weight calculation") {
  REQUIRE(g.getEdgeWeight(529, 2299) == 537);
}

TEST_CASE("Test node weight with invalid id") {
    REQUIRE(g.getNodeWeight(10000) == -1);
}
