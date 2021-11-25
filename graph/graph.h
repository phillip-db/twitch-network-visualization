#pragma once
#include <vector>
#include "../CSVParser/CSVParser.h"
#include "../streamer/streamer.h"

class Graph {
 public:
  Graph();
  Graph(const vector<Streamer>& streamers, unsigned numNodes);

  bool isAdjacent(unsigned id1, unsigned id2);
  vector<unsigned> getEdges(unsigned id);
  int getEdgeWeight(unsigned id1, unsigned id2);

 private:
  const unsigned kNumNodes = 7107;
  vector<Streamer> streamers_;
  vector<vector<unsigned>> adjMatrix_;
};