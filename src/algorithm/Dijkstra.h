//
// Created by chiewen on 2015/11/7.
//

#ifndef ROADINS_DIJKSTRA_H
#define ROADINS_DIJKSTRA_H

#include <memory>
#include <map>
#include <vector>
#include <set>
#include "../network/Node.h"
#include "../util/ptr_node_comp.h"

using namespace std;

class Dijkstra {
public:
    typedef vector<pair<shared_ptr<Node>, double>> neighbor_vec;

    static void find_nearest(const shared_ptr<Node> &ptr_node);

    static set<shared_ptr<Node>, ptr_node_less> top_k(const shared_ptr<Node> &ptr_node,
                              double dist_to_node, int k);

    static vector<shared_ptr<Road>>
            shortest_path(const shared_ptr<Node> &ptr_from, const shared_ptr<Node> &ptr_to);

private:
    typedef map<long, pair<double, shared_ptr<Node>>> known_map;
};


#endif //ROADINS_DIJKSTRA_H
