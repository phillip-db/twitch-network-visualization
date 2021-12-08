#pragma once
#include <random>
#include "graph/graph.h"
#include "streamer/streamer.h"
#include <utility>
#include <iostream>

using namespace std;

class GraphVisual {
  public:
    GraphVisual();
    GraphVisual(Graph graph, unsigned width, unsigned height);
    // GraphVisual();
    //attractForce();
    //repelForce();

    // drawNode(HSLAPixel::point center);
    // drawEdge(HSLAPixel::point center1, HSLAPixel::point center2);
    // checkNodeNodeOverlap(HSLAPixel::point center1, unsigned radius1, HSLAPixel::point center2, unsigned radius2);
    // checkBorderNodeOverlap(HSLAPixel::point center, unsigned radius);

    // drawGraph(); //calls drawAllNodes() and drawAllEdges()
    // drawAllNodes();
    // drawAlEdges();
    // findEdgePointOnCircle(HSLAPixel::point center1, unsigned radius1, HSLAPixel::point center2, unsigned radius2);


  private:
    unsigned CalcDistance(Node n1, Node n2);
    pair<unsigned, unsigned> CalcRepulsionForce(Node n1, Node n2);
    pair<unsigned, unsigned> CalcAttractionForce(Node n1, Node n2);
    
    struct Node {
      Node (unsigned r, pair<unsigned, unsigned> c, Streamer s) : radius(r), center(c), streamer(s) {};
      unsigned radius; //--based on views, average for dataset is 193,470
      pair<unsigned, unsigned> center;
      Streamer streamer;
    };

    Graph g_;

    unsigned width_;
    unsigned height_;
    unsigned kAverageViewers = 193470;

    vector<Node> nodes_;
    vector<vector<adjMatrix>> adjMatrix_;

    //vars found experimentally:
    /*
      #iterations for simulation
      optimal dist between vertices constant k = C * sqrt(area/num vertices)
    */
};
