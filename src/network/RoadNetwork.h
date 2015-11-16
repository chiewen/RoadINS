//
// Created by Chiewen on 2015/11/16.
//

#ifndef ROADINS_ROADNETWORK_H
#define ROADINS_ROADNETWORK_H

#include "boost/serialization/singleton.hpp"

#include "Node.h"
#include "../util/ptr_node_comp.h"
#include "../io/DataReader.h"

using boost::serialization::singleton;

class RoadNetwork : public singleton<vector<shared_ptr<Node>>> {
    static struct _init {
        _init();
    } __init;

public:
    static void reset();
    static void addSites(const vector<shared_ptr<Node>> &nodes, double ratio);
};


#endif //ROADINS_ROADNETWORK_H
