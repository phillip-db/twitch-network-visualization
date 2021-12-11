#pragma once
#include <vector>
#include "streamer.h"

using namespace std;

/** Class representing a Graph of weighted Streamer nodes with weighted edges */
class Graph {
 public:
  static const unsigned kNumNodes = 7126; // Change this to the number of nodes in a dataset

  /** Empty default constructor */
  Graph();

  /**
   * Constructs a graph from a vector of streamers.
   *
   * @param streamers Streamers to populate the Graph with.
   * @param numNodes Number of nodes the Graph should contain.
   */
  Graph(const vector<Streamer>& streamers, unsigned numNodes);

  /**
   * Determines the shortest path between two nodes using Dijkstra's shortest
   * path algorithm.
   *
   * Computes the shortest path between source and all other connected
   * nodes, but will only return the path to the goal node.
   *
   * @param source The source node.
   * @param goal The destination node.
   * @return a vector of Streamer names in order from beginning to end. If there
   * is no valid path, there will only be one element of the returned vector.
   */
  vector<string> Dijkstra(unsigned source, unsigned goal);

  /**
   * Traverses the graph using Breadth-First Search algorithm.
   *
   * @param source The starting node.
   * @return a vector of Streamers in the order they are visited.
   */
  vector<string> BFS(unsigned source);

  bool isAdjacent(unsigned id1, unsigned id2);
  vector<unsigned> getEdges(unsigned id);
  int getEdgeWeight(unsigned id1, unsigned id2);
  int getNumStreamers();
  int getNodeWeight(unsigned id);
  vector<Streamer> getStreamers();
  vector<vector<unsigned>> getAdjMatrix();

 private:
  vector<Streamer> streamers_;
  vector<vector<unsigned>> adjMatrix_;
  unsigned numNodes_;

  /**
   * Recursive helper function for building the shortest path in Djikstra's.
   *
   * @param parent Vector containing the parent nodes at given indices.
   * @param goal The destination node.
   * @param path Vector of Streamers along the shortest path.
   */
  void recursePath(vector<int> parent, int goal, vector<string>& path);

  /**
   * Helper function that computes the minimum distance between unvisited nodes.
   *
   * @param distance Vector of distances from starting node to another node.
   * @param visited Vector to keep track of visited nodes.
   * @return The minimum distance.
   */
  int getMinimumDistance(vector<int> distance, vector<bool> visited);
};