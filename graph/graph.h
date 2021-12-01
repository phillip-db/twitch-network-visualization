#pragma once
#include <vector>
#include "../CSVParser/CSVParser.h"
#include "../streamer/streamer.h"

class Graph {
 public:
  static const unsigned kNumNodes = 7107;

  Graph();
  Graph(const vector<Streamer>& streamers, unsigned numNodes);

  bool isAdjacent(unsigned id1, unsigned id2);
  vector<unsigned> getEdges(unsigned id);
  int getEdgeWeight(unsigned id1, unsigned id2);
  int getNumStreamers();
  int getNodeWeight(unsigned id);

 private:
  vector<Streamer> streamers_;
  vector<vector<unsigned>> adjMatrix_;
};