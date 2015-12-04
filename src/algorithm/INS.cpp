//
// Created by chiewen on 2015/11/13.
//

#include <algorithm>
#include <set>
#include "INS.h"
#include "Dijkstra.h"

void INS::move(Trajectory trajectory) {
    client_start();
    top_k.clear();
    ins.clear();

    refresh(k, top_k, ptr_top_k, ins, trajectory.get_then_forward());

    for (auto pos = trajectory.get_then_forward(); trajectory.has_next(); pos = trajectory.get_then_forward()) {
        if (!Dijkstra::verify(k, pos.first->to.lock(), pos.second, top_k, ins))
            ++communication, refresh(k, top_k, ptr_top_k, ins, pos);
        ++total_step;
    }
    client_pause();
}

void INS::refresh(int k, set<long> &top_k, set<PNode, ptr_node_less> &ptr_top_k, set<long> &ins,
                  const pair<PRoad, double> &pos) {
    client_to_server();
    Dijkstra::top_k(pos.first->to.lock(), pos.second, k, top_k, ptr_top_k, page);
    ins.clear();
    for (auto &t : ptr_top_k) {
        auto &neighbors = t->voronoi_neighbors;
        set_difference(neighbors.begin(), neighbors.end(), top_k.begin(), top_k.end(), inserter(ins, ins.end()));
    }
    server_to_client();
}
