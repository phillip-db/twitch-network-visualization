#include "utils.h"
#include "CSVParser.h"
#include "graph.h"

using namespace std;

int main() {
  CSVParser parser;
  vector<Streamer> output;
  output = parser.parseFile("data/modified_english_target.csv",
                            "data/musae_ENGB_edges.csv");
  Graph g;
  int numNodes = Graph::kNumNodes;
  g = Graph(output, numNodes);

  vector<string> traversal = g.BFS(0);
  utils::printPath(traversal);
  return 0;
}