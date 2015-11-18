//
// Created by chiewen on 2015/11/13.
//

#include <algorithm>
#include <set>
#include "MkNN.h"
#include "Dijkstra.h"

void MkNN::move(Trajectory trajectory, int k) {
    set<weak_ptr<Node>, ptr_node_less> top_k, ins;

    for (auto pos = trajectory.get_then_forward(); trajectory.has_next(); pos = trajectory.get_then_forward()) {
        top_k = Dijkstra::top_k(pos.first->to.lock(), pos.second, k);

        for (auto &t : top_k) {
            auto &neighbors = t.lock()->voronoi_neighbors;
            set_difference(neighbors.begin(), neighbors.end(), top_k.begin(), top_k.end(), inserter(ins, ins.end()),
                           ptr_node_less());
        }


    }
}
