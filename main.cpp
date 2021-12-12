#include <iostream>
#include "CSVParser.h"
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "graph.h"
#include "graph_visual.h"

using namespace std;
int main(int argc, char* argv[]) {
  if (argc != 4) {
    cout << "Incorrect number of arguments (need 3)." << endl;
    return 0;
  }

  int arg1 = stoi(argv[1]);
  int arg2 = stoi(argv[2]);
  int arg3 = stoi(argv[3]);

  CSVParser parser;
  vector<Streamer> output;
  output = parser.parseFile("data/modified_english_target.csv",
                            "data/musae_ENGB_edges.csv");
  Graph g;
  int numNodes = Graph::kNumNodes;

  g = Graph(output, numNodes);
  GraphVisual gv = GraphVisual(g, arg1, arg1, arg2, arg3);

  PNG* original = new PNG(arg1, arg1);
  gv.drawGraph(*original);
  original->writeToFile("original_graph.png");

  gv.Arrange();
  PNG* final = new PNG(arg1, arg1);
  gv.drawGraph(*final);
  final->writeToFile("final_graph.png");
}
