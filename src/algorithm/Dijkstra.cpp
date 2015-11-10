//
// Created by chiewen on 2015/11/7.
//
#include <map>
#include <set>
#include <algorithm>
#include <iostream>

#include "Dijkstra.h"

using namespace std;

void Dijkstra::find_nearest(const vector<shared_ptr<Node>> &vec_nodes, const shared_ptr<Node> &ptr_node) {
    map<long, pair<double, shared_ptr<Node>>> known_nodes;
    known_nodes[ptr_node->id] = make_pair(0.0, ptr_node);
    auto nearest = execute(vec_nodes, known_nodes, 1);
    if (nearest.size() == 1)
        ptr_node->nearest_neighbor = nearest[0];
    else throw runtime_error("node does not have nearest neighbor");
}

vector<pair<weak_ptr<Node>, double>>
Dijkstra::execute(
        const vector<shared_ptr<Node>> &vec_nodes,
        map<long, pair<double, shared_ptr<Node>>> &known_nodes, int k) {
    vector<pair<weak_ptr<Node>, double>> result;
    set<long> searched;

    while (!known_nodes.empty()) {
        auto min = min_element(known_nodes.begin(), known_nodes.end(),
                               [](const pair<long, pair<double, shared_ptr<Node>>> &l,
                                  const pair<long, pair<double, shared_ptr<Node>>> &r) {
                                   return l.second.first < r.second.first;
                               });

        auto p_min = min->second.second;
        if (p_min->isSite) {
            result.emplace_back(p_min, min->second.first);
            if (result.size() == k) break;
        }

        auto d_min = min->second.first;
        searched.insert(p_min->id);
        known_nodes.erase(min);

        for (auto n: p_min->neighbors()) {
            auto pn = n.first.lock();
            if (searched.find(pn->id) != searched.end()) continue;

            auto m = known_nodes.find(pn->id);
            if (m == known_nodes.end())
                known_nodes[pn->id] = make_pair(d_min + n.second, pn);
            else if (m->second.first > d_min + n.second)
                m->second.first = d_min + n.second;
        }
    }
    return result;
}

vector<pair<weak_ptr<Node>, double>>
Dijkstra::top_k(const vector<shared_ptr<Node>> &vec_nodes,
                const shared_ptr<Node> &ptr_node, double dist_to_node, int k) {
    map<long, pair<double, shared_ptr<Node>>> known_nodes;
    known_nodes[ptr_node->id] = make_pair(dist_to_node, ptr_node);
    return execute(vec_nodes, known_nodes, k);
}
