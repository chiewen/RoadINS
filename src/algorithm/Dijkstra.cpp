//
// Created by chiewen on 2015/11/7.
//
#include <map>
#include <set>
#include <algorithm>
#include <iostream>

#include "Dijkstra.h"

using namespace std;

void Dijkstra::execute(const shared_ptr<Node> &ptr_node, const vector<shared_ptr<Node>> &vec_nodes) {
    map<long, pair<double, shared_ptr<Node>>> known_nodes;
    set<long> searched;

    known_nodes[ptr_node->id] = make_pair(0.0, ptr_node);

    while (!known_nodes.empty()) {
        auto min = min_element(known_nodes.begin(), known_nodes.end(),
                               [](const pair<long, pair<double, shared_ptr<Node>>> &l,
                                  const pair<long, pair<double, shared_ptr<Node>>> &r) {
                                   return l.second.first < r.second.first;
                               });

        auto p_min = min->second.second;
        if (p_min->isSite) {
            ptr_node->nearest_neighbor = make_pair(p_min, min->second.first);
            break;
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
}
