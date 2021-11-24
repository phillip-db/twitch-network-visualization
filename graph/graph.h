#pragma once

class Graph {
  public:
    Graph(int nodes);
    void addEdge(int node1, int node2);
    void BFS(int source);

  private:
    int nodes_; //# of nodes
    list<int> *adjacency;
};