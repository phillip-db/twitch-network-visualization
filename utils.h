#pragma once
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;
/** Utility functions for the project */
namespace utils {
/**
 * Prints a vector of strings in a path format,
 * where each entry is separated by "->."
 */
void printPath(vector<string> path);

/**
 * Calculates distance between two cartesian points
 *
 * @param p1 First point.
 * @param p2 Second point.
 * @return cartesian distance between the points.
 */
double distance(pair<unsigned, unsigned> p1, pair<unsigned, unsigned> p2);
}  // namespace utils