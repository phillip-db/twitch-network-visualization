#pragma once

class GraphVisual {
 public:
  // GraphVisual();
  // attractForce();
  // repelForce();

  // drawNode(HSLAPixel::point center);
  // drawEdge(HSLAPixel::point center1, HSLAPixel::point center2);
  // getForcedBasedDistance();
  // checkNodeNodeOverlap(HSLAPixel::point center1, unsigned radius1,
  // HSLAPixel::point center2, unsigned radius2);
  // checkBorderNodeOverlap(HSLAPixel::point center, unsigned radius);

  // drawGraph(); //calls drawAllNodes() and drawAllEdges()
  // drawAllNodes();
  // drawAlEdges();
  // findEdgePointOnCircle(HSLAPixel::point center1, unsigned radius1,
  // HSLAPixel::point center2, unsigned radius2);

 private:
  // struct Node {
  //   unsigned radius; --based on views, average for dataset is 193,470
  //   HSLAPixel::point center;
  //   unsigned viewers;
  // }

  // unsigned width_;
  // unsigned height_;

  // vars found experimentally:
  /*
    #iterations for simulation
    optimal dist between vertices constant k = C * sqrt(area/num vertices)
  */
};
