#include <algorithm>
#include <iostream>
#include "../cs225/catch/catch.hpp"
#include "../graph.h"
#include "../graph_visual.h"
#include "../utils.h"

using namespace std;

TEST_CASE("Test arrange repulsion") {
  Streamer s1 = Streamer(0, "A", 1000000, 100, vector<unsigned>{});
  Streamer s2 = Streamer(1, "B", 1000000, 150, vector<unsigned>{});

  vector<Streamer> streamers = vector<Streamer>{s1, s2};

  Graph g(streamers, 2);

  GraphVisual gv = GraphVisual(g, 1000, 1000, 2, 1);

  pair<int, int> og1 = gv.getNodeCenter(0);
  pair<int, int> og2 = gv.getNodeCenter(1);
  double ogDist = utils::distance(og1, og2);

  gv.Arrange();

  pair<int, int> fin1 = gv.getNodeCenter(0);
  pair<int, int> fin2 = gv.getNodeCenter(1);
  double finDist = utils::distance(fin1, fin2);

  REQUIRE(finDist > ogDist);
}

TEST_CASE("Test arrange attraction") {
  Streamer s1 = Streamer(0, "A", 1000000, 100, vector<unsigned>{1, 2, 3});
  Streamer s2 = Streamer(1, "B", 1000000, 150, vector<unsigned>{0, 2, 3});
  Streamer s3 = Streamer(2, "C", 1000000, 100, vector<unsigned>{0, 1, 3});
  Streamer s4 = Streamer(3, "D", 1000000, 150, vector<unsigned>{0, 1, 2});

  vector<Streamer> streamers = vector<Streamer>{s1, s2, s3, s4};

  Graph g(streamers, 4);

  GraphVisual gv = GraphVisual(g, 1000, 1000, 4, 10000);

  pair<int, int> og1 = gv.getNodeCenter(0);
  pair<int, int> og2 = gv.getNodeCenter(1);
  double ogDist = utils::distance(og1, og2);

  gv.Arrange();

  pair<int, int> fin1 = gv.getNodeCenter(0);
  pair<int, int> fin2 = gv.getNodeCenter(1);
  double finDist = utils::distance(fin1, fin2);

  REQUIRE(finDist - ogDist <
          200.0);  // Will initially repulse, but equalize to global minima
}