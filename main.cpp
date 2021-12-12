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

  GraphVisual gv = GraphVisual(g, 8000, 8000);
  
  PNG* png = new PNG(8000, 8000);

  vector<GraphVisual::Node> nodes = gv.getNodes();

  gv.drawAllEdges(*png);

  for(unsigned i = 0; i < nodes.size(); i++) {
    if (nodes[i].center.first > 0 && nodes[i].center.second > 0) {
      gv.drawNode(nodes[i], *png);
    }
  }

  png->writeToFile("graph_visual1.png");

  gv.Arrange();

  nodes = gv.getNodes();

  PNG* png2 = new PNG(8000, 8000);

  gv.drawAllEdges(*png2);

  for(unsigned i = 0; i < nodes.size(); i++) {
    if (nodes[i].center.first > 0 && nodes[i].center.second > 0) {
      gv.drawNode(nodes[i], *png2);
    }
  }

  png2->writeToFile("graph_vis2.png");
}
