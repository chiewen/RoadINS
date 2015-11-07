//
// Created by chiewen on 2015/11/6.
//

#ifndef ROADINS_ROAD_H
#define ROADINS_ROAD_H

#include <memory>
#include <utility>

#include "Node.h"

class Road {
public:
    std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> terminals;
    double distance;

public:
    Road(std::shared_ptr<Node> &t1, std::shared_ptr<Node> &t2, double distance);
};


#endif //ROADINS_ROAD_H
