#include "graph.h"

Graph::Graph(int nodes){
  nodes_ = nodes;
}

void Graph::addEdge(int node1, int node2){
  adjacency[node1].push_back(node2);
}

//perform BFS traversal
void Graph::BFS(int source){
  //https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/

  queue<unsigned> queue;
  //visited vector

  while (!queue.empty()) {

  }
}
//adjacency list impl
//https://www.softwaretestinghelp.com/graph-implementation-cpp/

//graph impl
//https://stackoverflow.com/questions/5493474/graph-implementation-c