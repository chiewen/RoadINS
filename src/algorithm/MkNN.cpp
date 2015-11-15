//
// Created by chiewen on 2015/11/13.
//

#include <algorithm>
#include <c++/iostream>
#include <set>
#include "MkNN.h"
#include "Dijkstra.h"

void MkNN::move(Trajectory trajectory, int k) {
    for (auto pos = trajectory.get_then_forward(); trajectory.has_next(); pos = trajectory.get_then_forward()) {
        auto top_k = Dijkstra::top_k(pos.first->to.lock(), pos.second, k);

        set<shared_ptr<Node>, ptr_node_less> ins{};
        for (auto &k : top_k) {
            auto neighbors = k->neighbors();
            sort(neighbors.begin(), neighbors.end(), ptr_node_less());
            set_difference(neighbors.begin(), neighbors.end(), top_k.begin(), top_k.end(), inserter(ins, ins.end()),
                           ptr_node_less());
        }

        cout << endl << "topk:";
        for (auto &p: top_k) cout << p->id << " ";
        cout << endl << "ins:";
        for (auto &p: ins) cout << p->id << " ";
        cout << endl;

    }
}
