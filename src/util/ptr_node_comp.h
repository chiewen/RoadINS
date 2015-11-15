//
// Created by chiewen on 2015/11/15.
//

#ifndef ROADINS_PTR_NODE_COMP_H
#define ROADINS_PTR_NODE_COMP_H

#include "../network/Node.h"

struct ptr_node_less{
    bool operator()(const shared_ptr<Node> &pn1, const shared_ptr<Node> &pn2) { return pn1->id < pn2->id; }
};

struct ptr_node_equal {
    bool operator()(const shared_ptr<Node> &pn1, const shared_ptr<Node> &pn2) { return pn1->id == pn2->id; }
};

#endif //ROADINS_PTR_NODE_COMP_H
