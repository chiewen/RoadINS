//
// Created by chiewen on 2015/11/24.
//

#include "VStar.h"
#include "Dijkstra.h"

VStar::VStar(int x) : x(x) { }

void VStar::move(Trajectory trajectory, int k) {
    ordered_top_k.clear();
    ordered_top_k.reserve(k + x);

    auto p = trajectory.get_then_forward();
    Dijkstra::top_k_vstar(p.first->to.lock(), p.second, k + x, ordered_top_k);

    for (auto pos = trajectory.get_then_forward(); trajectory.has_next();
         pos = trajectory.get_then_forward())
        if (!validate_knn(pos, k, x)) calculate(pos, k, x);
}

void VStar::calculate(const pair<PRoad, double> &pos, int k, int x) {

}

bool VStar::validate_knn(const pair<PRoad, double> &pos, int k, int x) {
    //validate Fixed Rank Region (FRR)
    long from_id = pos.first->from.lock()->id;
    long to_id = pos.first->to.lock()->id;



    //validate the safe region with regard to the k'th nearest neighbor

    return false;
}
