//
// Created by chiewen on 2015/11/24.
//

#include "VStar.h"
#include "Dijkstra.h"

void VStar::move(Trajectory trajectory, int k) {
    set<long> top_k;
    set<PNode, ptr_node_less> ptr_top_k;

    auto pos = trajectory.get_then_forward();
    Dijkstra::top_k(pos.first->to.lock(), pos.second, k + x, top_k, ptr_top_k);
}

VStar::VStar(int x) : x(x) { }
