#include "utils.h"
#include "CSVParser.h"
#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 2) { 
    cout << "Incorrect number of arguments (need 1)." << endl;
    return 0;
  }

  CSVParser parser;
  vector<Streamer> output;
  output = parser.parseFile("data/modified_english_target.csv",
                            "data/musae_ENGB_edges.csv");
  Graph g;
  int numNodes = Graph::kNumNodes;
  g = Graph(output, numNodes);
  
  int id = stoi(argv[1]);

  if (id < 0 || id >= numNodes) cout << "Invalid id." << endl;

  vector<string> traversal = g.BFS(id);
  utils::printPath(traversal);
  cout << "Number of nodes in connected component: " << traversal.size() << endl;
  return 0;
}