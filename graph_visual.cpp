#include "graph_visual.h"
#include <cmath>

using namespace std;

GraphVisual::GraphVisual() {}

GraphVisual::GraphVisual(Graph graph, unsigned width, unsigned height) {
    //steal adjacency matrix
    //create node from streamers
    g_ = graph;
    width_ = width;
    height_ = height;

    vector<Streamer> streamers = g_.getStreamers();

    for (Streamer s : streamers) {
        unsigned randX = rand()%(width + 1);
        unsigned randY = rand()%(height + 1);
        pair<unsigned, unsigned> coords = make_pair(randX, randY);

        // modify this for size of node, viewers = e^radius - 1
        unsigned radius = log(s.getViews() + 1); //standardizes radius based on range of views

        Node n(radius, coords, s); //creates a node for each streamer with random intial position

        nodes_.push_back(n);
    }

    adjMatrix_ = g_.getAdjMatrix();

    forceConst_ = kAreaConst * (sqrt((width_*height_)/g_.getStreamers().size()));
}

float CalcAngle(pair<unsigned, unsigned> thisPoint, pair<unsigned,unsigned> otherPoint) {
    int delX = thisPoint.first - otherPoint.first;
    int delY = thisPoint.second - otherPoint.second;

    float angleDegrees = atan2(delY, delX) * 180/3.1415;

    return angleDegrees * - 1;
}

pair<double, double> CalcComponents(double force, float angleDeg) {
    double xComp = force * sin(angleDeg * 3.1415/180);
    double yComp = force * cos(angleDeg * 3.1415/180);

    return make_pair(xComp, yComp);
}
double GraphVisual::CalcDistance(Node n1, Node n2) {
    unsigned x = n1.center.first - n2.center.first;
    unsigned y = n1.center.second - n2.center.second;

    double dist = sqrt(pow(x,2) + pow(y,2));

    return dist;
}

pair<double, double> GraphVisual::CalcAttractionForce(Node n1, Node n2) {

    double distance = CalcDistance(n1, n2);

    double a_force = pow(distance, 2)/forceConst_;

    return pair<double, double>(0.0, 0.0); // replace this   
}