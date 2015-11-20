//
// Created by chiewen on 2015/11/7.
//

#ifndef ROADINS_NODE_H
#define ROADINS_NODE_H

#include <vector>
#include <memory>
#include <mutex>
#include <set>
#include "../util/ptr_node_comp.h"

using namespace std;

class Road;

struct Node {
    long id;
    bool isSite = false;
    double x, y;

    pair<weak_ptr<Node>, double> nearest_site;

    set<long> voronoi_neighbors;
    mutex mutex_voronoi;

    vector<shared_ptr<Road>> roads;
    mutex mutex_roads;

    Node(long id, double x, double y);
};

#endif //ROADINS_NODE_H
