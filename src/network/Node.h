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
    set<weak_ptr<Node>, ptr_node_less> voronoi_neighbors;

    vector<shared_ptr<Road>> roads;
    mutex mutex_roads;

    Node(long id, double x, double y);
    vector<pair<shared_ptr<Node>, shared_ptr<Road>>> neighbors_with_road();
    vector<shared_ptr<Node>> neighbors();
};

#endif //ROADINS_NODE_H
