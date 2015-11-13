//
// Created by chiewen on 2015/11/6.
//

#ifndef ROADINS_ROAD_H
#define ROADINS_ROAD_H

#include <memory>
#include <utility>

class Node;

using namespace std;

class Road {
public:
    weak_ptr<Node> from;
    weak_ptr<Node> to;
    double distance;

public:
    Road(const shared_ptr<Node> &t1, const shared_ptr<Node> &t2, double distance);
};


#endif //ROADINS_ROAD_H
