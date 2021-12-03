#pragma once
#include <vector>
#include "../streamer/streamer.h"

using namespace std;

class Graph {
 public:
  static const unsigned kNumNodes = 7126;

  Graph();
  Graph(const vector<Streamer>& streamers, unsigned numNodes);

  bool isAdjacent(unsigned id1, unsigned id2);
  vector<unsigned> getEdges(unsigned id);
  int getEdgeWeight(unsigned id1, unsigned id2);
  int getNumStreamers();
  int getNodeWeight(unsigned id);
  void Dijsktra(unsigned source, unsigned goal);
  int getMinimumDistance(vector<int> distance, vector<bool> visited);
  void printPath(vector<int> parent, int goal);

 private:
  vector<Streamer> streamers_;
  vector<vector<unsigned>> adjMatrix_;
  unsigned numNodes_;
};