//
// Created by chiewen on 2015/11/6.
//

#ifndef ROADINS_ROAD_H
#define ROADINS_ROAD_H

#include <memory>
#include <utility>

#include "Node.h"

using namespace std;

class Road {
public:
    pair<weak_ptr<Node>, weak_ptr<Node>> terminals;
    double distance;

public:
    Road(const shared_ptr<Node> &t1, const shared_ptr<Node> &t2, double distance);
};


#endif //ROADINS_ROAD_H
