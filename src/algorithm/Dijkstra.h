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
    static void find_nearest(const vector<shared_ptr<Node>> &vec_nodes, const shared_ptr<Node> &ptr_node);

    static vector<pair<weak_ptr<Node>, double>>
            top_k(const vector<shared_ptr<Node>> &vec_nodes, const shared_ptr<Node> &ptr_node,
                  double dist_to_node, int k);

private:
    static vector<pair<weak_ptr<Node>, double>>
            execute(const vector<shared_ptr<Node>> &vec_nodes,
                    map<long, pair<double, shared_ptr<Node>>> &known_nodes,
                    int k);
};


#endif //ROADINS_DIJKSTRA_H
