#pragma once
#include <vector>
#include "streamer.h"

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
  vector<string> Dijkstra(unsigned source, unsigned goal);
  vector<string> BFS(unsigned source);
  int getMinimumDistance(vector<int> distance, vector<bool> visited);
  vector<Streamer> getStreamers();
  vector<vector<unsigned>> getAdjMatrix();

 private:
  vector<Streamer> streamers_;
  vector<vector<unsigned>> adjMatrix_;
  unsigned numNodes_;

  void recursePath(vector<int> parent, int goal, vector<string>& path);
};