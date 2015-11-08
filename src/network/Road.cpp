//
// Created by chiewen on 2015/11/7.
//

#include "Road.h"

Road::Road(const std::shared_ptr<Node> &t1, const std::shared_ptr<Node> &t2, double distance) :
        terminals(std::make_pair(std::weak_ptr<Node>(t1), std::weak_ptr<Node>(t2))), distance(distance) { }