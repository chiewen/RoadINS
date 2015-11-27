//
// Created by chiewen on 2015/11/13.
//

#include <algorithm>
#include <set>
#include "INS.h"
#include "Dijkstra.h"

void INS::move(Trajectory trajectory, int k) {
    set<long> top_k, ins;
    set<PNode, ptr_node_less> ptr_top_k;
    refresh(k, top_k, ptr_top_k, ins, trajectory.get_then_forward());

    for (auto pos = trajectory.get_then_forward(); trajectory.has_next(); pos = trajectory.get_then_forward())
        if (!Dijkstra::verify(k, pos.first->to.lock(), pos.second, top_k, ins))
            refresh(k, top_k, ptr_top_k, ins, pos);
}

void INS::refresh(int k, set<long> &top_k, set<PNode, ptr_node_less> &ptr_top_k, set<long> &ins,
                  const pair<PRoad, double> &pos) {
    Dijkstra::top_k(pos.first->to.lock(), pos.second, k, top_k, ptr_top_k);
    ins.clear();
    for (auto &t : ptr_top_k) {
        auto &neighbors = t->voronoi_neighbors;
        set_difference(neighbors.begin(), neighbors.end(), top_k.begin(), top_k.end(), inserter(ins, ins.end()));
    }
}
