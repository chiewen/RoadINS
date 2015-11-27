//
// Created by Chiewen on 2015/11/16.
//


#include "../network/Node.h"

bool ptr_node_less::operator()(const PNode &pn1, const PNode &pn2) { return pn1->id < pn2->id; }
