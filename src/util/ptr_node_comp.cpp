//
// Created by Chiewen on 2015/11/16.
//


#include "../network/Node.h"

bool ptr_node_less::operator()(const shared_ptr<Node> &pn1, const shared_ptr<Node> &pn2) { return pn1->id < pn2->id; }

bool ptr_node_equal::operator()(const shared_ptr<Node> &pn1, const shared_ptr<Node> &pn2) { return pn1->id == pn2->id; }