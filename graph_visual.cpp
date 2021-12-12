#include "graph_visual.h"
#include <time.h>
#include <algorithm>
#include <cmath>
#include "utils.h"

using namespace std;
using namespace cs225;

using unit = double;
using point = pair<unit, unit>;

// namespace for point and force calculations
namespace fdpoint {

inline unit att(unit x, unit k) noexcept { return x * x / k; }

inline unit rep(unit x, unit k) noexcept { return k * k / x; }

inline unit norm(point const& p) noexcept {
  return sqrt(p.first * p.first + p.second * p.second);
}

inline point operator+(point const& a, point const& b) noexcept {
  return {a.first + b.first, a.second + b.second};
}

inline point operator-(point const& p) noexcept {
  return {-p.first, -p.second};
}

inline point operator-(point const& a, point const& b) noexcept {
  return {a.first - b.first, a.second - b.second};
}

inline point operator*(point const& p, unit const d) noexcept {
  return {p.first * d, p.second * d};
}

inline point operator/(point const& p, unit const d) noexcept {
  return {p.first / d, p.second / d};
}

inline point& operator+=(point& a, point const& b) noexcept {
  a.first += b.first;
  a.second += b.second;
  return a;
}

inline point& operator-=(point& a, point const& b) noexcept {
  a.first -= b.first;
  a.second -= b.second;
  return a;
}

}  // namespace fdpoint

using namespace fdpoint;

GraphVisual::GraphVisual() {}

GraphVisual::GraphVisual(Graph graph, unsigned width, unsigned height,
                         unsigned size, unsigned iterations) {
  g_ = graph;
  width_ = width;
  height_ = height;
  iterations_ = iterations;

  vector<Streamer> streamers = g_.getStreamers();
  nodes_ = vector<Node>(size);

  // srand(time(NULL)); // uncomment for random node placement between calls of
  // ./visualize
  for (unsigned s = 0; s < size; s++) {
    int randX = rand() % (width + 1);
    int randY = rand() % (height + 1);
    pair<int, int> coords = make_pair(randX, randY);

    unsigned radius = kRadiusGrouping[kRadiusGrouping.size() - 1].second;
    unsigned hue = 0;

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

  forceConst_ = sqrt(width_ * height_ / nodes_.size());
}

void GraphVisual::Arrange() {
  for (unsigned l = 0; l < iterations_; l++) {
    vector<point> displacement(nodes_.size(), {0.0, 0.0});

    // repulsion forces
    for (unsigned i = 0; i < nodes_.size() - 1; i++) {
      for (unsigned j = i + 1; j < nodes_.size(); j++) {
        Node& n1 = nodes_[i];
        Node& n2 = nodes_[j];
        point posi = n1.center;
        point posj = n2.center;

        auto delta = posi - posj;
        auto ad = norm(delta);
        auto diff = delta / ad * rep(ad, forceConst_);

        displacement[i] += diff;
        displacement[j] -= diff;
      }
    }

    // attraction forces
    for (unsigned i = 0; i < nodes_.size(); i++) {
      for (unsigned j : nodes_[i].streamer.getFriends()) {
        if (j < nodes_.size()) {
          Node& n1 = nodes_[i];
          Node& n2 = nodes_[j];
          point posi = n1.center;
          point posj = n2.center;

          auto delta = posi - posj;
          auto ad = norm(delta);
          auto diff = delta / ad * att(ad, forceConst_);

          displacement[i] -= diff;
        }
      }
    }

    // displace all nodes
    for (unsigned i = 0; i < displacement.size(); i++) {
      Node& n1 = nodes_[i];
      point posi = n1.center;

      posi += displacement[i] / norm(displacement[i]) *
              min(kMaxDisp, norm(displacement[i]));
      n1.center = posi;
    }
  }
}

void GraphVisual::drawGraph(PNG& png) {
  drawAllEdges(png);
  drawAllNodes(png);
}

void GraphVisual::drawEdge(const Node& n1, const Node& n2, PNG& png) {
  int x1 = n1.center.first;
  int x2 = n2.center.first;
  int y1 = n1.center.second;
  int y2 = n2.center.second;

  // Ensure that no Node is out of bounds
  if (x1 <= 0 || x2 <= 0 || x1 > static_cast<int>(width_) ||
      x2 > static_cast<int>(width_) || y1 <= 0 || y2 <= 0 ||
      y1 > static_cast<int>(height_) || y2 > static_cast<int>(height_))
    return;

  if (x2 < x1) {  // We want to draw left to right, so swap values if necessary
    swap(x1, x2);
    swap(y1, y2);
  }

  double slope = static_cast<double>(y2 - y1) / (x2 - x1);

  int y_st = y1;

  for (int x = x1; x < x2; x++) {
    int y = slope * (x - x1) + y1;
    int y_i = y_st;

    // Drawing logic to ensure clean, full lines
    do {
      HSLAPixel& p = png.getPixel(x, y_i);
      p.l = 0;

      if (y_i < y) y_i++;
      if (y_i > y) y_i--;
    } while (y_i != y);
    y_st = y;
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
  int rect_x1 = n.center.first - n.radius;
  int rect_y1 = n.center.second - n.radius;
  int rect_x2 = n.center.first + n.radius;
  int rect_y2 = n.center.second + n.radius;

  for (int x = rect_x1; x < rect_x2; x++) {
    for (int y = rect_y1; y < rect_y2; y++) {
      pair<int, int> curr = make_pair(x, y);
      double dist = utils::distance(curr, n.center);

      // Only draw the Node if its center is in bounds
      if (dist < n.radius && x > 0 && x < static_cast<int>(width_) && y > 0 &&
          y < static_cast<int>(height_)) {
        HSLAPixel& p = png.getPixel(x, y);
        p.h = n.hue;
        p.s = 1;
        p.l = 0.5;
        p.a = 1;
      }
    }
  }
}

void GraphVisual::drawAllNodes(PNG& png) {
  for (unsigned i = 0; i < nodes_.size(); i++) {
    drawNode(nodes_[i], png);
  }
}

pair<int, int> GraphVisual::getNodeCenter(unsigned id) {
  return nodes_[id].center;
}