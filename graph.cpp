#include "graph.h"
#include <limits.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>

using namespace std;

Graph::Graph() {}

Graph::Graph(const vector<Streamer>& streamers, unsigned numNodes) {
  numNodes_ = numNodes;
  streamers_.resize(numNodes);
  adjMatrix_.resize(numNodes);
  for (unsigned i = 0; i < adjMatrix_.size(); i++) {
    adjMatrix_[i].resize(numNodes);
  }

  for (Streamer s : streamers) {
    streamers_[s.getId()] = s;
  }

  for (Streamer s : streamers) {
    for (unsigned f : s.getFriends()) {
      adjMatrix_[s.getId()][f] = getEdgeWeight(s.getId(), f);
    }
  }
}

void Graph::Dijkstra(unsigned source, unsigned goal) {
  vector<int> distance =
      vector<int>(numNodes_, INT_MAX);  // vectorfor calculating smalles
                                        // distance from source to every node
  vector<bool> visited = vector<bool>(numNodes_, false);
  vector<int> parent = vector<int>(numNodes_, -1);

  distance[source] = 0;  // distance from source to source is 0

  for (unsigned i = 0; i < numNodes_ - 1; i++) {
    int x = getMinimumDistance(distance, visited);
    visited[x] = true;
    // update distance of neighboring vertex
    for (unsigned y = 0; y < numNodes_; y++) {
      if (!visited[y] && isAdjacent(x, y) && distance[x] != INT_MAX &&
          distance[x] + static_cast<int>(adjMatrix_[x][y]) < distance[y]) {
        parent[y] = x;
        distance[y] = distance[x] + getEdgeWeight(x, y);
      }
    }
  }

  cout << streamers_[source].getName();
  printPath(parent, goal);
  cout << endl;
}

void Graph::BFS(unsigned source) {
  vector<bool> visited = vector<bool>(numNodes_, false);

  visited[source] = true;
  queue<unsigned> q;
  q.push(source);

  while (!q.empty()) {
    unsigned curr = q.front();
    q.pop();

    // get i where adjMatrix[curr][i] == 1
    // enqueue all the i's

    vector<pair<unsigned, unsigned>> adjacent;

    for (unsigned i = 0; i < adjMatrix_[curr].size(); i++) {
      if (adjMatrix_[curr][i] != 0 && !visited[i]) {
        adjacent.push_back(make_pair(adjMatrix_[curr][i], i));
      }
    }

    sort(adjacent.begin(), adjacent.end());

    for (auto id : adjacent) {
      q.push(id.second);
    }

    visited[curr] = true;
    // cout << curr
  }
  // cout << endl;
}

int Graph::getMinimumDistance(vector<int> distance, vector<bool> visited) {
  int currentMin = INT_MAX;
  int index = -1;  // shouldnt set to -1 probably

  for (unsigned i = 0; i < numNodes_; i++) {
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
  return adjMatrix_[id1][id2];  // > 0;
}

vector<unsigned> Graph::getEdges(unsigned id) {
  vector<unsigned> out;
  if (id < adjMatrix_.size()) {
    for (unsigned i = 0; i < adjMatrix_[id].size(); i++) {
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