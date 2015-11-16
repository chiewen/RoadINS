//
// Created by chiewen on 2015/11/15.
//

#ifndef ROADINS_PTR_NODE_COMP_H
#define ROADINS_PTR_NODE_COMP_H

class Node;

using namespace std;

struct ptr_node_less{
    bool operator()(const shared_ptr<Node> &pn1, const shared_ptr<Node> &pn2);
};

struct ptr_node_equal {
    bool operator()(const shared_ptr<Node> &pn1, const shared_ptr<Node> &pn2);
};

#endif //ROADINS_PTR_NODE_COMP_H
