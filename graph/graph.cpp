#include "graph.h"
#include <cmath>
#include <limits.h>

using namespace std;

Graph::Graph() {}
Graph::Graph(const vector<Streamer>& streamers, unsigned numNodes) {
  numNodes_ = numNodes;
  streamers_.resize(numNodes);
  adjMatrix_ = vector<vector<unsigned>>(numNodes, vector<unsigned>(numNodes, 0));

  for (Streamer s : streamers) {
    for (unsigned f : s.getFriends()) {
      adjMatrix_[s.getId()][f] = 1;
    }
    streamers_[s.getId()] = s;
  }
}

void Graph::Dijsktra(vector<vector<unsigned>> adjMatrix, unsigned source) {
  vector<int> distance;  // vectorfor calculating smalles distance from source to every node
  vector<bool> visited;
  visited.resize(numNodes_, INT_MAX);
  distance.resize(numNodes_, -1);

  distance[source] = 0; // distance from source to source is 0

  for (unsigned i = 0; i < numNodes_; i++) {
    int index = getMinimumDistance(distance, visited);
    visited[index] = 1;
    // update distance of neighboring vertex
  }

  // use priority queue
  // build minHeap
}

int Graph::getMinimumDistance(vector<int> distance, vector<bool> visited) {
  int currentMin = INT_MAX;
  int index = -1; // shouldnt set to -1 probably

  for (int i = 0; i < numNodes_; i++) {
    if (!visited[i] && distance[i] <= currentMin) {
      currentMin = distance[i];
      index = i;
    }
    // may need to account if if statement never is done?
  }
  return index;

}

bool Graph::isAdjacent(unsigned id1, unsigned id2) {
  if (id1 >= adjMatrix_.size() || id2 >= adjMatrix_.size() || id1 == id2) return false;
  return adjMatrix_[id1][id2]; // == 1;
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
  if (id1 >= adjMatrix_.size() || id2 >= adjMatrix_.size() || id1 == id2) return -1;
  return abs(static_cast<int>(streamers_[id1].getAge()) - static_cast<int>(streamers_[id2].getAge()));
}

int Graph::getNumStreamers() {
  return streamers_.size();
}

int Graph::getNodeWeight(unsigned id) {
  if (id < streamers_.size()) {
    return streamers_[id].getViews();
  }
  return -1;
}