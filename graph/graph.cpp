#include "graph.h"
#include <limits.h>
#include <cmath>
#include <iostream>

using namespace std;

Graph::Graph() {}
Graph::Graph(const vector<Streamer>& streamers, unsigned numNodes) {
  numNodes_ = numNodes;
  streamers_.resize(numNodes);
  adjMatrix_.resize(numNodes);
  for (int i = 0; i < adjMatrix_.size(); i++) {
    adjMatrix_[i].resize(numNodes);
  }

  for (Streamer s : streamers) {
    for (unsigned f : s.getFriends()) {
      adjMatrix_[s.getId()][f] = 1;
    }
    streamers_[s.getId()] = s;
  }
}

void Graph::Dijsktra(unsigned source, unsigned goal) {
  vector<int> distance = vector<int>(numNodes_, INT_MAX);  // vectorfor calculating smalles distance from source
                         // to every node
  vector<bool> visited = vector<bool>(numNodes_, false);
  vector<int> parent = vector<int>(numNodes_, -1);

  distance[source] = 0;  // distance from source to source is 0

  for (unsigned i = 0; i < numNodes_ - 1; i++) {
    int x = getMinimumDistance(distance, visited);
    visited[x] = true;
    // update distance of neighboring vertex
    for (int y = 0; y < numNodes_; y++) {
      if (!visited[y] && isAdjacent(x, y) && distance[x] != INT_MAX &&
          distance[x] + getEdgeWeight(x, y) < distance[y]) {
        parent[y] = x;
        distance[y] = distance[x] + getEdgeWeight(x, y);
      }
    }
  }

  cout << streamers_[source].getName();
  printPath(parent, goal);
  cout << endl;
}

int Graph::getMinimumDistance(vector<int> distance, vector<bool> visited) {
  int currentMin = INT_MAX;
  int index = -1;  // shouldnt set to -1 probably

  for (int i = 0; i < numNodes_; i++) {
    if (!visited[i] && distance[i] <= currentMin) {
      currentMin = distance[i];
      index = i;
    }
    // may need to account if if statement never is done?
  }
  return index;
}

void Graph::printPath(vector<int> parent, int goal) {
  if (parent[goal] == -1) return;
  printPath(parent, parent[goal]);
  cout << "->" << streamers_[goal].getName();
}

bool Graph::isAdjacent(unsigned id1, unsigned id2) {
  if (id1 >= adjMatrix_.size() || id2 >= adjMatrix_.size() || id1 == id2)
    return false;
  return adjMatrix_[id1][id2];  // == 1;
}

vector<unsigned> Graph::getEdges(unsigned id) {
  vector<unsigned> out;
  if (id < adjMatrix_.size()) {
    for (int i = 0; i < adjMatrix_[id].size(); i++) {
      if (adjMatrix_[id][i]) out.push_back(i);
    }
  }
  return out;
}

int Graph::getEdgeWeight(unsigned id1, unsigned id2) {
  if (id1 >= adjMatrix_.size() || id2 >= adjMatrix_.size() || id1 == id2)
    return -1;
  return abs(static_cast<int>(streamers_[id1].getAge()) -
             static_cast<int>(streamers_[id2].getAge()));
}

int Graph::getNumStreamers() { return streamers_.size(); }

int Graph::getNodeWeight(unsigned id) {
  if (id < streamers_.size()) {
    return streamers_[id].getViews();
  }
  return -1;
}