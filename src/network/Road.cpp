//
// Created by chiewen on 2015/11/7.
//

#include "Road.h"

Road::Road(std::shared_ptr<Node> &t1, std::shared_ptr<Node> &t2, double distance) :
        terminals(make_pair(t1, t2)), distance(distance) { }