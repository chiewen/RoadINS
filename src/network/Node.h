//
// Created by chiewen on 2015/11/7.
//

#ifndef ROADINS_NODE_H
#define ROADINS_NODE_H

#include <vector>
#include <memory>
#include <mutex>

#include "Road.h"

using namespace std;

struct Node {
    long id;
    bool isSite = false;
    double x, y;
    pair<weak_ptr<Node>, double> nearest_neighbor;
    vector<shared_ptr<Road>> roads;
    mutex mutex_roads;

    Node(long id, double x, double y);
    vector<pair<shared_ptr<Node>, shared_ptr<Road>>> neighbors();
};

#endif //ROADINS_NODE_H
