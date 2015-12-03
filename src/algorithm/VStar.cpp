//
// Created by chiewen on 2015/11/24.
//

#include <iostream>
#include "VStar.h"
#include "Dijkstra.h"

VStar::VStar(int k, int x) : k(k), x(x) { }

void VStar::move(Trajectory trajectory) {
    ordered_k_x.clear();
    ordered_k_x.reserve(k + x);

    calculate(trajectory.get_then_forward());

    for (auto pos = trajectory.get_then_forward(); trajectory.has_next();
         pos = trajectory.get_then_forward())
        if (!validate_knn(pos)) calculate(pos);
}

void VStar::calculate(const pair<PRoad, double> &pos) {
    cout << "!!!!" << endl;
    Dijkstra::top_k_vstar(pos.first->to.lock(), pos.second, k + x, ordered_k_x);
    q_b = pos;
    z = ordered_k_x[k + x - 1];
    z_dist = Dijkstra::distance_to(pos.first->to.lock(), pos.second, z);
}

bool VStar::validate_knn(const pair<PRoad, double> &pos) {
    cout << "new pos" << endl;
    //refresh Fixed Rank Region (FRR)
    long from_id = pos.first->from.lock()->id;
    long to_id = pos.first->to.lock()->id;

    typedef typename FrrMap::mapped_type FrrKX;

    auto pFrom = frrMap.find(from_id);
    if (pFrom == frrMap.end()) {
        FrrKX topk;
        Dijkstra::top_k_with_distance(pos.first->from.lock(), k + x, ordered_k_x, topk);
        pFrom = frrMap.insert(make_pair(from_id, topk)).first;
    }

    auto pTo = frrMap.find(to_id);
    if (pTo == frrMap.end()) {
        FrrKX topk;
        Dijkstra::top_k_with_distance(pos.first->to.lock(), k + x, ordered_k_x, topk);
        pTo = frrMap.insert(make_pair(to_id, topk)).first;
    }

    bool should_recalculate = true;
    while(should_recalculate) {
        should_recalculate = false;
        for (int i = 0; i < k + x - 1; i++)
            if (min(pFrom->second[ordered_k_x[i]->id] + pos.first->distance - pos.second,
                    pTo->second[ordered_k_x[i]->id] + pos.second) >
                min(pFrom->second[ordered_k_x[i + 1]->id] + pos.first->distance - pos.second,
                    pTo->second[ordered_k_x[i + 1]->id] + pos.second)) {
                swap(ordered_k_x[i], ordered_k_x[i + 1]);
                should_recalculate = true;
                cout << i << " : " << ordered_k_x[i]->id << " : " << ordered_k_x[i+1]->id <<endl;
            }
    }

    if (z->id != ordered_k_x[k + x - 1]->id) {
        z = ordered_k_x[k + x - 1];
        z_dist = Dijkstra::distance_to(q_b.first->to.lock(), q_b.second, z);
    }

    //validate the safe region with regard to the k'th nearest neighbor
    return z_dist > Dijkstra::distance_to(pos.first->to.lock(), pos.second, ordered_k_x[k - 1]) +
                    Dijkstra::distance_to(pos.first->to.lock(), pos.second + q_b.second, q_b.first->to.lock());
}
