#pragma once
#include <iostream>
#include <vector>

using namespace std;

void printPath(vector<string> path) {
  for (unsigned i = 0; i < path.size(); i++) {
    cout << path[i];
    if (i < path.size() - 1) cout << "->";
  }
  cout << endl;
}
