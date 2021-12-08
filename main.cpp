#include <iostream>
#include "CSVParser.h"
#include "graph.h"
#include "graph_visual.h"
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"


using namespace std;

int main() {

  CSVParser parser;
  vector<Streamer> output;
  output = parser.parseFile("data/modified_english_target.csv",
                            "data/musae_ENGB_edges.csv");
  Graph g;
  int numNodes = Graph::kNumNodes;

  g = Graph(output, numNodes);

  GraphVisual gv = GraphVisual(g, 1000, 1000);
  
}
