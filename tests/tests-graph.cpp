#include <algorithm>
#include <iostream>
#include "../CSVParser.h"
#include "../cs225/catch/catch.hpp"
#include "../graph.h"
#include "../utils.h"

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

TEST_CASE("Dijkstra") {
  vector<string> valid_path = g.Dijkstra(2299, 529);
  vector<string> invalid_path = g.Dijkstra(2299, 0);
  REQUIRE(valid_path[0] == "CaptainTeabeard");
  REQUIRE(valid_path[1] == "EnderKate");
  REQUIRE(invalid_path[0] == "No valid path.");
}

TEST_CASE("BFS") {
  vector<string> traversal = g.BFS(2299);
  vector<string> expected = vector<string>(14);
  expected[0] = "CaptainTeabeard";
  expected[1] = "EnderKate";
  REQUIRE(traversal == expected);
}