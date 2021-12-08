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

float GraphVisual::CalcAngle(pair<unsigned, unsigned> thisPoint, pair<unsigned,unsigned> otherPoint) {
    int delX = thisPoint.first - otherPoint.first;
    int delY = thisPoint.second - otherPoint.second;

    float angleDegrees = atan2(delY, delX) * 180/M_PI;

    return angleDegrees;
}

pair<double, double> GraphVisual::CalcComponents(double force, float angleDeg) {
    double xComp = force * cos(angleDeg * M_PI/180);
    double yComp = force * sin(angleDeg * M_PI/180);

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

    float angle = CalcAngle(n1.center, n2.center);

    pair<double, double> components = CalcComponents(a_force, angle);

    return components;
}

pair<double, double> GraphVisual::CalcRepulsionForce(Node n1, Node n2) {

    double distance = CalcDistance(n1, n2);

    double a_force = -1 * pow(forceConst_,2)/distance;

    float angle = CalcAngle(n1.center, n2.center);

    pair<double, double> components = CalcComponents(a_force, angle);

    return components;
}

void GraphVisual::Arrange() {
    unsigned count = 0;
    double sumDisplacement = 0;
    while(count < kMaxIterations && sumDisplacement < KDisplaceThreshold) {
        sumDisplacement = 0;
        vector<pair<double, double>> nodeVelocities;
        for (unsigned i = 0; i < nodes_.size(); i++) {
            vector<pair<double, double>> netForce;
            for (unsigned j = 0; j < nodes_.size(); j++) {
                if (i != j) {
                    netForce.push_back(CalcRepulsionForce(nodes_[i], nodes_[j]));
                }
                if (adjMatrix_[nodes_[i].streamer.getId()][nodes_[i].streamer.getId()] > 0) {
                    netForce.push_back(CalcAttractionForce(nodes_[i], nodes_[j]));
                }
            }
            double xNet = 0;
            double yNet = 0;
            for (pair<double,double> p : netForce) { //sum up the net force
                xNet += p.first;
                yNet += p.second;
            }

            nodeVelocities.push_back(make_pair(xNet, yNet));
        }
        for (unsigned v = 0; v < nodeVelocities.size(); v++) {
            if (nodeVelocities[v].first < 0) {
                nodes_[v].center.first -= nodeVelocities[v].first;
            } else {
                nodes_[v].center.first += nodeVelocities[v].first;
            }

            if (nodeVelocities[v].second < 0) {
                nodes_[v].center.second -= nodeVelocities[v].second;
            } else {
                nodes_[v].center.second += nodeVelocities[v].second;
            }
        }

        for (pair<double, double> p : nodeVelocities) {
            sumDisplacement += sqrt(pow(p.first, 2) + pow(p.second,2)); 
        }
        count++;
    }
}

