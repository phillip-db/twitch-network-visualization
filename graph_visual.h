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

/** Class that places nodes onto a graph and arranges them based on the
 * Fruchterman-Reingold algorithm */
class GraphVisual {
 public:
  /** Struct representing Nodes on the graph */
  struct Node {
    /** Default Node constructor */
    Node() {
      radius = 0;
      center = make_pair(0, 0);
      streamer = Streamer();
      hue = 0;
      velocity = make_pair(0.0, 0.0);
      nextCenter = center;
    }

    /**
     * Constructs a parameterized node.
     *
     * @param r Radius of the Node.
     * @param c Center coordinates of the node.
     * @param s Streamer that the Node represents.
     * @param h Hue of the Node when drawn.
     */
    Node(unsigned r, pair<int, int> c, Streamer s, unsigned h)
        : radius(r), center(c), streamer(s), hue(h) {
      velocity = make_pair(0.0, 0.0);
      nextCenter = c;
    };

    unsigned radius;  // based on views
    pair<int, int> center;
    Streamer streamer;
    unsigned hue;
    pair<double, double> velocity;
    pair<int, int> nextCenter;
  };

  /** Empty default constructor */
  GraphVisual();

  /**
   * Constructs a parameterized GraphVisual object.
   *
   * @param graph Graph that will be visualized.
   * @param width Width of the graph bounds.
   * @param height Height of the graph bounds.
   * @param size The number of Nodes to place onto the visualization.
   * @param iterations The number of iterations of Arrange to run.
   */
  GraphVisual(Graph graph, unsigned width, unsigned height, unsigned size,
              unsigned iterations);

  /** Arranges the Nodes on the graph according to the Fruchterman-Reingold
   * algorithm */
  void Arrange();

  /**
   * Draws the Graph visualization.
   *
   * @param png The PNG to draw the Graph on.
   */
  void drawGraph(PNG& png);

  pair<int, int> getNodeCenter(unsigned id);

 private:
  // Constant vector used in assigning Node radii based on num views:
  // {num_views, radius}
  vector<pair<unsigned, unsigned>> kRadiusGrouping = {
      {0, 15},      {7500, 25},    {25000, 40},     {100000, 50},
      {250000, 60}, {1000000, 70}, {10000000, 100}, {178000000, 70}};

  // Constant vector used in assigning Node color - corresponds to radius size
  vector<unsigned> kHueVector = {279, 246, 224, 186, 99, 44, 25, 0};
  double kMaxDisp = 80.0;

  Graph g_;
  unsigned width_;
  unsigned height_;
  unsigned iterations_;
  unsigned forceConst_;
  vector<Node> nodes_;

  /**
   * Draws a Node.
   *
   * @param n The Node to draw.
   * @param png The PNG to draw on.
   */
  void drawNode(const Node& n, PNG& png);

  /**
   * Draws the edge between two Nodes.
   *
   * @param n1 The first Node.
   * @param n2 The second Node.
   * @param png The PNG to draw on.
   */
  void drawEdge(const Node& n1, const Node& n2, PNG& png);

  /**
   * Draws all edges onto the PNG.
   *
   * @param png The PNG to draw on.
   */
  void drawAllEdges(PNG& png);

  /**
   * Draws all Nodes on to the PNG.
   *
   * @param png The PNG to draw on.
   */
  void drawAllNodes(PNG& png);
};
