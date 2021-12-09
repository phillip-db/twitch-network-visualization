#pragma once
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

namespace utils {
void printPath(vector<string> path) {
  for (unsigned i = 0; i < path.size(); i++) {
    cout << path[i];
    if (i < path.size() - 1) cout << "->";
  }
  cout << endl;
}

double distance(pair<unsigned, unsigned> p1, pair<unsigned, unsigned> p2) {
  int xDist = p2.first - p1.first;
  int yDist = p2.second - p1.second;
  double distance = sqrt((xDist * xDist) + (yDist * yDist));
  return distance;
}
}  // namespace utils