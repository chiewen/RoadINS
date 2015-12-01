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
#include "../network/Road.h"

using namespace std;

class Dijkstra {
public:
    static void find_nearest(const PNode &ptr_node);

    static void top_k(const PNode &ptr_node,
                      double dist_to_node, int k, set<long> &top_k,
                      set<PNode, ptr_node_less> &ptr_top_k);

    static void top_k_vstar(const PNode &ptr_node,
                                      double dist_to_node, int k, vector<PNode> &top_k);

    static vector<PRoad>
            shortest_path(const PNode &ptr_from, const PNode &ptr_to);

    static bool verify(int k, const PNode &query_object, double dist_to_next,
                       const set<long> &top_k, const set<long> &ins);

    static double distance_to(const PNode &ptr_from, double dist, const PNode &ptr_to);

private:
    typedef map<long, pair<double, PNode>> known_map;
};


#endif //ROADINS_DIJKSTRA_H
