#include <iostream>
#include "CSVParser.h"
#include "graph.h"
#include "utils.h"

using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 3) {
    cout << "Incorrect number of arguments (need 2)" << endl;
    return 0;
  }

  CSVParser parser;
  vector<Streamer> output;
  output = parser.parseFile("data/modified_english_target.csv",
                            "data/musae_ENGB_edges.csv");
  Graph g;
  int numNodes = Graph::kNumNodes;

  int s1 = -1;
  int s2 = -1;

  // Verify that Streamers exist in dataset
  for (Streamer s : output) {
    if (s.getName() == argv[1]) {
      s1 = s.getId();
    }
    if (s.getName() == argv[2]) {
      s2 = s.getId();
    }
  }

  if (s1 == -1) cout << "First streamer is invalid." << endl;
  if (s2 == -1) cout << "Second streamer is invalid." << endl;
  if (s1 == -1 || s2 == -1) return 0;

  g = Graph(output, numNodes);
  vector<string> path = g.Dijkstra(s1, s2);
  utils::printPath(path);

  return 0;
}
