#include <iostream>
#include "graph/graph.h"
#include "CSVParser/CSVParser.h"

int main() {
  CSVParser parser;
  vector<Streamer> output;
  output = parser.parseFile("data/modified_english_target.csv", "data/musae_ENGB_edges.csv");
  Graph g;
  int numNodes = Graph::kNumNodes;

  g = Graph(output, numNodes);
  g.Dijsktra(0, 900);

  return 0;
}
