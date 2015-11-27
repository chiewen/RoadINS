//
// Created by chiewen on 2015/11/6.
//

#ifndef ROADINS_ROAD_H
#define ROADINS_ROAD_H

#include <memory>
#include <utility>

#include "Node.h"

using namespace std;

struct Road {
    weak_ptr<Node> from;
    weak_ptr<Node> to;
    double distance;

    Road(const PNode &t1, const PNode &t2, double distance);
};

typedef shared_ptr<Road> PRoad;


#endif //ROADINS_ROAD_H
