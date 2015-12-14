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

class RoadNetwork : public singleton<vector<PNode>> {
    static struct _init {
        _init();
    } __init;

public:
    static void reset(double ratio = 0, long length = 0);
    static void add_sites(const vector<PNode> &nodes, double ratio);
    static void set_nearest(const vector<PNode> &nodes);
    static void reset_ratio(double ratio);
};


#endif //ROADINS_ROADNETWORK_H
