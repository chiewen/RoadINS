//
// Created by chiewen on 2015/11/24.
//

#include "VStar.h"
#include "Dijkstra.h"

VStar::VStar(int k, int x) : k(k), x(x) { }

void VStar::move(Trajectory trajectory) {
    client_start();
    ordered_k_x.clear();
    ordered_k_x.reserve(k + x);

    calculate(trajectory.get_then_forward());

    for (auto pos = trajectory.get_then_forward(); trajectory.has_next();
         pos = trajectory.get_then_forward()) {
        ++total_step;
        if (!validate_knn(pos)) ++communication, calculate(pos);
    }
    client_pause();
}

void VStar::calculate(const pair<PRoad, double> &pos) {
    client_to_server();
    Dijkstra::top_k_vstar(pos, k + x, ordered_k_x, page);
    q_b = pos;
    z = ordered_k_x[k + x - 1];
    z_dist = Dijkstra::distance_to(pos.first->to.lock(), pos.second, z);
    server_to_client();
}

bool VStar::validate_knn(const pair<PRoad, double> &pos) {
    long from_id = pos.first->from.lock()->id;
    long to_id = pos.first->to.lock()->id;
    auto pFrom = frrMap.find(from_id);
    if (pFrom == frrMap.end()) {
        map<long, double> topk;
        Dijkstra::top_k_with_distance(pos.first->from.lock(), k + x, ordered_k_x, topk);
        pFrom = frrMap.insert(make_pair(from_id, topk)).first;
    }

    auto pTo = frrMap.find(to_id);
    if (pTo == frrMap.end()) {
        map<long, double> topk;
        Dijkstra::top_k_with_distance(pos.first->to.lock(), k + x, ordered_k_x, topk);
        pTo = frrMap.insert(make_pair(to_id, topk)).first;
    }

    bool should_recalculate = true;
    while (should_recalculate) {
        should_recalculate = false;
        for (int i = 0; i < k + x - 1; i++)
            if (min(pTo->second[ordered_k_x[i]->id] + pos.second,
                    pFrom->second[ordered_k_x[i]->id] + pos.second - pos.second) >
                min(pTo->second[ordered_k_x[i + 1]->id] + pos.second,
                    pFrom->second[ordered_k_x[i + 1]->id] + pos.second - pos.second)) {
                if (i >= x) return false;
                swap(ordered_k_x[i], ordered_k_x[i + 1]);
                should_recalculate = true;
            }
    }

    if (z->id != ordered_k_x[k + x - 1]->id) {
        z = ordered_k_x[k + x - 1];
        z_dist = Dijkstra::distance_to_bidirection(q_b, z);
    }

    return z_dist > Dijkstra::distance_to_bidirection(pos, ordered_k_x[k - 1]) +
                    min(Dijkstra::distance_to_bidirection(pos, q_b.first->to.lock()) + q_b.second,
                        Dijkstra::distance_to_bidirection(pos, q_b.first->from.lock()) + q_b.first->distance -
                        q_b.second);
}
