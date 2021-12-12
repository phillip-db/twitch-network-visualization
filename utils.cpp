#include "utils.h"

namespace utils {
void printPath(vector<string> path) {
  for (unsigned i = 0; i < path.size(); i++) {
    cout << path[i];
    if (i < path.size() - 1) cout << "->";
  }
  cout << endl;
}

double distance(pair<int, int> p1, pair<int, int> p2) {
  int xDist = static_cast<int>(p2.first) - static_cast<int>(p1.first);
  int yDist = static_cast<int>(p2.second) -static_cast<int>(p1.second);
  double dist = sqrt((xDist * xDist) + (yDist * yDist));
  return dist;
}
}  // namespace utils