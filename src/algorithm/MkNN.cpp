//
// Created by chiewen on 2015/11/13.
//

#include <algorithm>
#include "MkNN.h"
#include "Dijkstra.h"

void MkNN::move(Trajectory trajectory, int k) {
    for (auto pos = trajectory.get_then_forward(); trajectory.has_next(); pos = trajectory.get_then_forward()) {
        auto top_k = Dijkstra::top_k(pos.first->to.lock(), pos.second, k);
        vector<shared_ptr<Node>> ins;
        for (auto &t: top_k)
            for (auto &n: t.first->neighbors()) {
                if (find_if(top_k.begin(), top_k.end(), [&](const pair<shared_ptr<Node>, double> &tk) {
                    return t.first->id == tk.first->id;
                }) == top_k.end()) {
                    ins.emplace_back(n.first);
                }
            }

    }
}
