//
// Created by chiewen on 2015/11/7.
//

#ifndef ROADINS_DIJKSTRA_H
#define ROADINS_DIJKSTRA_H

#include <memory>
#include <vector>
#include "../network/Node.h"

using namespace std;

class Dijkstra {
public:
    static void execute(const shared_ptr<Node> &ptr_node, const vector<shared_ptr<Node>> &vec_nodes);
};


#endif //ROADINS_DIJKSTRA_H
