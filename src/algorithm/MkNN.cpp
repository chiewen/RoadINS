//
// Created by chiewen on 2015/11/13.
//

#include <algorithm>
#include <set>
#include <iostream>
#include "MkNN.h"
#include "Dijkstra.h"

void MkNN::move(Trajectory trajectory, int k) {
    set<long> top_k, ins;
    set<weak_ptr<Node>, ptr_node_less> ptr_top_k;
        refresh(k, top_k, ptr_top_k, ins, trajectory.get_then_forward());

    for (auto pos = trajectory.get_then_forward(); trajectory.has_next(); pos = trajectory.get_then_forward())
        if (!Dijkstra::verify(k, pos.first->from.lock(), pos.second, top_k, ins))
            refresh(k, top_k, ptr_top_k, ins, pos);

}

void MkNN::refresh(int k, set<long> &top_k, set<weak_ptr<Node>, ptr_node_less> &ptr_top_k, set<long> &ins,
                   const pair<shared_ptr<Road>, double> &pos) {
    Dijkstra::top_k(pos.first->to.lock(), pos.second, k, top_k, ptr_top_k);
    ins.clear();
    for (auto &t : ptr_top_k) {
        auto &neighbors = t.lock()->voronoi_neighbors;
        set_difference(neighbors.begin(), neighbors.end(), top_k.begin(), top_k.end(), inserter(ins, ins.end()));
    }

    cout << "top k\t";
    for (auto l: top_k) cout << l << " ";
    cout << endl << "ins\t" << ins.size() << "\t";
    for (auto l: ins) cout << l << " ";
    cout << endl;

}
