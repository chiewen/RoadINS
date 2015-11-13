//
// Created by chiewen on 2015/11/7.
//
#include <map>
#include <set>
#include <algorithm>
#include <iostream>
#include <tuple>

#include "Dijkstra.h"
#include "../network/Road.h"

using namespace std;

void Dijkstra::find_nearest(const shared_ptr<Node> &ptr_node) {
    known_map known_nodes;
    known_nodes[ptr_node->id] = make_pair(0.0, ptr_node);
    auto nearest = execute(known_nodes, 1);
    if (nearest.size() == 1)
        ptr_node->nearest_neighbor = nearest[0];
    else throw runtime_error("node does not have nearest neighbor");
}

Dijkstra::neighbor_vec Dijkstra::execute(known_map &known_nodes, int k) {
    neighbor_vec result;
    set<long> searched;
    while (!known_nodes.empty()) {
        typedef known_map::value_type map_value;
        auto min = min_element(known_nodes.begin(), known_nodes.end(),
                               [](const map_value &l, const map_value &r) { return l.second.first < r.second.first; });
        auto p_min = min->second.second;
        if (p_min->isSite) {
            result.emplace_back(p_min, min->second.first);
            if (result.size() == k) break;
        }
        auto d_min = min->second.first;
        searched.insert(p_min->id);
        known_nodes.erase(min);
        for (auto n: p_min->neighbors()) {
            auto pn = n.first;
            if (searched.find(pn->id) != searched.end()) continue;
            auto m = known_nodes.find(pn->id);
            if (m == known_nodes.end())
                known_nodes[pn->id] = make_pair(d_min + n.second->distance, pn);
            else if (m->second.first > d_min + n.second->distance)
                m->second.first = d_min + n.second->distance;
        }
    }
    return result;
}

Dijkstra::neighbor_vec Dijkstra::top_k(const shared_ptr<Node> &ptr_node, double dist_to_node, int k) {
    known_map known_nodes;
    known_nodes[ptr_node->id] = make_pair(dist_to_node, ptr_node);
    return execute(known_nodes, k);
}

vector<shared_ptr<Road>> Dijkstra::shortest_path(const shared_ptr<Node> &ptr_from, const shared_ptr<Node> &ptr_to) {
    vector<shared_ptr<Road>> result;
    map<long, tuple<double, shared_ptr<Node>, shared_ptr<Road>>> known_nodes;
    known_nodes[ptr_from->id] = make_tuple(0, ptr_from, nullptr);
    map<long, shared_ptr<Road>> searched;
    while (!known_nodes.empty()) {
        typedef remove_reference<decltype(known_nodes)>::type::value_type map_value;
        auto min = min_element(known_nodes.begin(), known_nodes.end(),
                               [](const map_value &l, const map_value &r) {
                                   return get<0>(l.second) < get<0>(r.second);
                               });
        auto p_min = get<1>(min->second);
        auto d_min = get<0>(min->second);
        searched[p_min->id] = get<2>(min->second);
        known_nodes.erase(min);

        if (p_min->id == ptr_to->id) {
            for (auto previous = searched[p_min->id]; previous; previous = searched.at(previous->from.lock()->id))
                result.push_back(previous);
            break;
        }
        else
            for (auto n: p_min->neighbors()) {
                auto pn = n.first;
                if (searched.find(pn->id) != searched.end()) continue;
                auto m = known_nodes.find(pn->id);
                if (m == known_nodes.end())
                    known_nodes[pn->id] = make_tuple(d_min + n.second->distance, pn, n.second);
                else if (get<0>(m->second) > d_min + n.second->distance) {
                    get<0>(m->second) = d_min + n.second->distance;
                    get<2>(m->second) = n.second;
                }
            }
    }
    return result;
}
