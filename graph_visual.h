#pragma once
#include <iostream>
#include <random>
#include <utility>
#include <vector>
#include "cs225/PNG.h"
#include "graph.h"
#include "streamer.h"

using namespace std;
using namespace cs225;

class GraphVisual {
 public:
  struct Node {
    Node() {
      radius = 0;
      center = make_pair(0, 0);
      streamer = Streamer();
      hue = 0;
      velocity = make_pair(0.0, 0.0);
      nextCenter = center;
    }
    Node(unsigned r, pair<int, int> c, Streamer s, unsigned h)
        : radius(r), center(c), streamer(s), hue(h) {
      velocity = make_pair(0.0, 0.0);
      nextCenter = c;
    };
    unsigned radius;  //--based on views, average for dataset is 193,470
    pair<int, int> center;
    Streamer streamer;
    unsigned hue;
    pair<double, double> velocity;
    pair<int, int> nextCenter;
  };
  GraphVisual();
  GraphVisual(Graph graph, unsigned width, unsigned height);
  void Arrange();

  void drawNode(const Node& n, PNG& png);
  vector<Node>& getNodes();
  void drawEdge(const Node& n1, const Node& n2, PNG& png);
  void drawAllEdges(PNG& png);

  // drawGraph(); //calls drawAllNodes() and drawAllEdges()
  // drawAllNodes();

 private:
  float CalcAngle(pair<int, int> thisPoint, pair<int, int> otherPoint);
  pair<double, double> CalcComponents(double force, float angleDeg);
  double CalcDistance(const Node& n1, const Node& n2);
  pair<double, double> CalcRepulsionForce(const Node& n1, const Node& n2);
  pair<double, double> CalcAttractionForce(const Node& n1, const Node& n2);

  Graph g_;

  unsigned width_;
  unsigned height_;
  unsigned forceConst_;

  vector<pair<unsigned, unsigned>> kRadiusGrouping = {
      {0, 15},      {7500, 25},    {25000, 40},    {100000, 50},
      {250000, 60}, {1000000, 70}, {10000000, 100}, {178000000, 70}};

  vector<unsigned> kHueVector = {279, 246, 224, 186, 99, 44, 25, 0};

  vector<Node> nodes_;
  vector<vector<unsigned>> adjMatrix_;
};
