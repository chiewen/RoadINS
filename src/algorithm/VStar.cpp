//
// Created by chiewen on 2015/11/24.
//

#include "VStar.h"
#include "Dijkstra.h"

VStar::VStar(int x) : x(x) { }

void VStar::move(Trajectory trajectory, int k) {
    vector<PNode> ordered_top_k;
    ordered_top_k.reserve(k + x);

    auto p = trajectory.get_then_forward();
    Dijkstra::top_k_vstar(p.first->to.lock(), p.second, k + x, ordered_top_k);

    for (auto pos = trajectory.get_then_forward(); trajectory.has_next();
         pos = trajectory.get_then_forward()) {

    }

}

