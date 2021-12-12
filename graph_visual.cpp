#include "graph_visual.h"
#include <algorithm>
#include <cmath>
#include "utils.h"
#include <time.h>

using namespace std;
using namespace cs225;

GraphVisual::GraphVisual() {}

GraphVisual::GraphVisual(Graph graph, unsigned width, unsigned height) {
  // steal adjacency matrix
  // create node from streamers
  g_ = graph;
  width_ = width;
  height_ = height;

  vector<Streamer> streamers = g_.getStreamers();
  nodes_ = vector<Node>(5);

  srand(time(NULL));
  for (unsigned s = 0; s < 5; s++) {
    int randX = rand() % (width + 1);
    int randY = rand() % (height + 1);
    pair<int, int> coords = make_pair(randX, randY);

    // modify this for size of node, viewers = e^radius - 1
    unsigned radius = kRadiusGrouping[kRadiusGrouping.size() - 1].second;
    unsigned hue = 0;
    // ((kUpperBound * (s.getViews() - kMinViews)) / (kMaxViews - kMinViews)) +
    // kShift; 2 * log(min(s.getViews(), kClipValue) + 1);  // standardizes
    // radius based on range of views */
    for (unsigned i = 1; i < kRadiusGrouping.size(); i++) {
      if (streamers[s].getViews() < kRadiusGrouping[i].first) {
        radius = kRadiusGrouping[i - 1].second;
        hue = kHueVector[i - 1];
        break;
      }
    }
    Node n(
        radius, coords, streamers[s],
        hue);  // creates a node for each streamer with random intial position

    nodes_[s] = n;
  }

  adjMatrix_ = g_.getAdjMatrix();

  forceConst_ =
      kAreaConst * (sqrt((width_ * height_) / nodes_.size()));
}

float GraphVisual::CalcAngle(pair<int, int> thisPoint,
                             pair<int, int> otherPoint) {
  int delX = thisPoint.first - otherPoint.first;
  int delY = thisPoint.second - otherPoint.second;

  float angleDegrees = atan2(delY, delX) * 180 / M_PI;

  return angleDegrees;
}

pair<double, double> GraphVisual::CalcComponents(double force, float angleDeg) {
  double xComp = force * cos(angleDeg * M_PI / 180);
  double yComp = force * sin(angleDeg * M_PI / 180);

  return make_pair(xComp, yComp);
}
double GraphVisual::CalcDistance(const Node& n1, const Node& n2) {
  unsigned x = n1.center.first - n2.center.first;
  unsigned y = n1.center.second - n2.center.second;

  double dist = sqrt(pow(x, 2) + pow(y, 2));

  return dist;
}

pair<double, double> GraphVisual::CalcAttractionForce(const Node& n1, const Node& n2) {
  double distance = CalcDistance(n1, n2);

  double a_force = kAttractConst * max(distance - kSpringDist, 0.0);

  float angle = CalcAngle(n1.center, n2.center);

  pair<double, double> components = CalcComponents(a_force, angle);

  return components;
}

pair<double, double> GraphVisual::CalcRepulsionForce(const Node& n1, const Node& n2) {
  double distance = CalcDistance(n1, n2);

  double a_force = -1 * (kRepConst / pow(distance, 2));

  float angle = CalcAngle(n1.center, n2.center);

  pair<double, double> components = CalcComponents(a_force, angle);

  return components;
}

void GraphVisual::Arrange() {
  int stopCount = 0;
  unsigned iters = 0;
  while(true) {
    double totalDisplacement = 0;

    for (unsigned i = 0; i < nodes_.size(); i++) {
      pair<int, int> currentPos = nodes_[i].center;
      pair<double, double> netForce = make_pair(0, 0);

      for (unsigned j = 0; j < nodes_.size(); j++) {
        if (j != i) {
          pair<double, double> repForce = CalcRepulsionForce(nodes_[i], nodes_[j]);
          netForce.first += repForce.first;
          netForce.second += repForce.second;
        }
      }

      for (unsigned j : nodes_[i].streamer.getFriends()) {
        if (j < nodes_.size() && adjMatrix_[i][j] > 0) {
          pair<double, double> attrForce = CalcAttractionForce(nodes_[i], nodes_[j]);
          netForce.first += attrForce.first;
          netForce.second += attrForce.second;
        }
      }

      nodes_[i].velocity.first *= kDamping;
      nodes_[i].velocity.second *= kDamping;
      nodes_[i].nextCenter.first += nodes_[i].velocity.first;
      nodes_[i].nextCenter.second += nodes_[i].velocity.second;
    }

    for (unsigned i = 0; i < nodes_.size(); i++) {
      int xDif = nodes_[i].nextCenter.first - nodes_[i].center.first;
      int yDif = nodes_[i].nextCenter.second - nodes_[i].center.second;
      totalDisplacement += sqrt(pow(xDif, 2) + pow(yDif, 2));
      nodes_[i].center = nodes_[i].nextCenter;
    }

    iters++;
    if (totalDisplacement < KDisplaceThreshold) stopCount++;
    if (stopCount > 3) break;
    if (iters > kMaxIterations) break;
  }
}

void GraphVisual::drawEdge(const Node& n1, const Node& n2, PNG& png) {
  unsigned x1 = n1.center.first;
  unsigned x2 = n2.center.first;
  unsigned y1 = n1.center.second;
  unsigned y2 = n2.center.second;

  if ((x1 == 0 && y1 == 0) || (x2 == 0 && y2 == 0)) return;

  if (x2 < x1) {
    swap(x1, x2);
    swap(y1, y2);
  }

  double slope = static_cast<double>(y2 - y1) / (x2 - x1);

  for (unsigned x = x1; x < x2; x++) {
    unsigned y = slope*(x - x1) + y1;
    HSLAPixel& p = png.getPixel(x, y);
    p.l = 0;
  }
}
void GraphVisual::drawAllEdges(PNG& png) {
  for (unsigned x = 0; x < nodes_.size(); x++) {
    for (unsigned y = 0; y < nodes_.size(); y++) {
      if (g_.isAdjacent(x, y) > 0) {
        drawEdge(nodes_[x], nodes_[y], png);
      }
    }
  }
}

void GraphVisual::drawNode(const Node& n, PNG& png) {
  unsigned rect_x1 = n.center.first - n.radius;
  unsigned rect_y1 = n.center.second - n.radius;
  unsigned rect_x2 = n.center.first + n.radius;
  unsigned rect_y2 = n.center.second + n.radius;

  for (unsigned x = rect_x1; x < rect_x2; x++) {
    for (unsigned y = rect_y1; y < rect_y2; y++) {
      pair<unsigned, unsigned> curr = make_pair(x, y);
      double dist = utils::distance(curr, n.center);
      if (dist < n.radius) {
        HSLAPixel& p = png.getPixel(x, y);
        p.h = n.hue;
        p.s = 1;
        p.l = 0.5;
        p.a = 1;
      }
    }
  }

  /* Square around center for testing
  for (unsigned x = n.center.first - 2; x < n.center.first + 2; x++) {
    for (unsigned y = n.center.second - 2; y < n.center.second + 2; y++) {
      HSLAPixel& p = png.getPixel(x, y);
      p.h = 319;
      p.s = 1;
      p.l = 0.5;
      p.a = 1;
    }
  }
  */
}

vector<GraphVisual::Node> GraphVisual::getNodes() { return nodes_; }