#include "graph_visual.h"
#include "graph/graph.h"
#include "streamer/streamer.h"
#include <cmath>

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
        unsigned radius = log(s.getViews + 1); //standardizes radius based on range of views

        Node n(radius, coords, s); //creates a node for each streamer with random intial position

        nodes_.push_back(n);
    }

    adjMatrix_ = g_.getAdjMatrix();
}

unsigned GraphVisual::CalcDistance(Node n1, Node n2) {
    unsigned x = n1.center.first - n2.center.first;
    unsigned y = n1.center.second - n2.center.second;

    dist = math.sqrt(math.pow(x,2) + math.pow(y,2));

    return <unsigned>dist;
}

// pair<unsigned, unsigned> GraphVisual::CalcAttractionForce(Node n1, Node n2) {

// }