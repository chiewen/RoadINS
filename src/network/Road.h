//
// Created by chiewen on 2015/11/6.
//

#ifndef ROADINS_ROAD_H
#define ROADINS_ROAD_H

#include <memory>
#include <utility>

#include "Node.h"

class Road {
    std::pair<std::shared_ptr<Node>> terminals;
public:
    Road(std::shared_ptr<Node> t1, std::shared_ptr<Node> t2): terminals(make_pair(t1, t2)){};
};


#endif //ROADINS_ROAD_H
