//
// Created by chiewen on 2015/11/7.
//
#include <map>
#include <set>
#include <algorithm>
#include <iostream>

#include "Dijkstra.h"
#include "../network/Road.h"

using namespace std;

void Dijkstra::find_nearest(const shared_ptr<Node> &ptr_node) {
    known_map known_nodes;
    known_nodes[ptr_node->id] = make_pair(0.0, ptr_node);

    typedef vector<pair<shared_ptr<Node>, double>> neighbor_vec;
    set<long> searched;
    while (!known_nodes.empty()) {
        typedef known_map::value_type map_value;
        auto min = min_element(known_nodes.begin(), known_nodes.end(),
                               [](const map_value &l, const map_value &r) { return l.second.first < r.second.first; });
        auto p_min = min->second.second;
        if (p_min->isSite) {
            ptr_node->nearest_site = make_pair(p_min, min->second.first);
            break;
        }
        auto d_min = min->second.first;
        searched.insert(p_min->id);
        known_nodes.erase(min);
        for (auto n: p_min->neighbors_with_road()) {
            auto pn = n.first;
            if (searched.find(pn->id) != searched.end()) continue;
            auto m = known_nodes.find(pn->id);
            if (m == known_nodes.end())
                known_nodes[pn->id] = make_pair(d_min + n.second->distance, pn);
            else if (m->second.first > d_min + n.second->distance)
                m->second.first = d_min + n.second->distance;
        }
    }
}


void Dijkstra::top_k(const shared_ptr<Node> &ptr_node, double dist_to_node, int k,
                                                   set<long> &top_k, set<weak_ptr<Node>, ptr_node_less> &ptr_top_k) {
    known_map known_nodes;
    known_nodes[ptr_node->id] = make_pair(dist_to_node, ptr_node);
    ptr_top_k.clear();
    set<long> searched;
    while (!known_nodes.empty()) {
        typedef known_map::value_type map_value;
        auto min = min_element(known_nodes.begin(), known_nodes.end(),
                               [](const map_value &l, const map_value &r) { return l.second.first < r.second.first; });
        auto p_min = min->second.second;
        if (p_min->isSite) {
            ptr_top_k.insert(p_min);
            if (ptr_top_k.size() == k) break;
        }
        auto d_min = min->second.first;
        searched.insert(p_min->id);
        known_nodes.erase(min);
        for (auto n: p_min->neighbors_with_road()) {
            auto &pn = n.first;
            if (searched.find(pn->id) != searched.end()) continue;
            auto m = known_nodes.find(pn->id);
            if (m == known_nodes.end())
                known_nodes[pn->id] = make_pair(d_min + n.second->distance, pn);
            else if (m->second.first > d_min + n.second->distance)
                m->second.first = d_min + n.second->distance;
        }
    }
    top_k.clear();
    transform(ptr_top_k.begin(), ptr_top_k.end(), inserter(top_k, top_k.begin()),
              [](const weak_ptr<Node> &n) { return n.lock()->id; });
}

vector<shared_ptr<Road>> Dijkstra::shortest_path(const shared_ptr<Node> &ptr_from, const shared_ptr<Node> &ptr_to) {
    vector<shared_ptr<Road>> result;
    map<long, tuple<double, shared_ptr<Node>, shared_ptr<Road>>> known_nodes;
    known_nodes.insert(make_pair(ptr_from->id, make_tuple(0, ptr_from, nullptr)));
    map<long, shared_ptr<Road>> searched;
    while (!known_nodes.empty()) {
        typedef remove_reference<decltype(known_nodes)>::type::value_type map_value;
        auto min = min_element(known_nodes.begin(), known_nodes.end(),
                               [](const map_value &l, const map_value &r) {
                                   return get<0>(l.second) < get<0>(r.second);
                               });
        auto p_min = get<1>(min->second);
        auto d_min = get<0>(min->second);
        searched.insert(make_pair(p_min->id, get<2>(min->second)));
        known_nodes.erase(min);

        if (p_min->id == ptr_to->id) {
            for (auto previous = searched[p_min->id]; previous; previous = searched.at(previous->from.lock()->id))
                result.push_back(previous);
            break;
        }
        else
            for (auto n: p_min->neighbors_with_road()) {
                auto &pn = n.first;
                if (searched.find(pn->id) != searched.end()) continue;
                auto m = known_nodes.find(pn->id);
                if (m == known_nodes.end())
                    known_nodes.insert(make_pair(pn->id, make_tuple(d_min + n.second->distance, pn, n.second)));
                else if (get<0>(m->second) > d_min + n.second->distance) {
                    get<0>(m->second) = d_min + n.second->distance;
                    get<2>(m->second) = n.second;
                }
            }
    }
    return result;
}

bool Dijkstra::verify(int k, const shared_ptr<Node> &query_object, double dist_to_next,
                      const set<long> &top_k, const set<long> &ins) {
    known_map known_nodes;
    known_nodes.insert(make_pair(query_object->id, make_pair(dist_to_next, query_object)));
    int count = 0;
    set<long> searched;
    while (!known_nodes.empty()) {
        typedef known_map::value_type map_value;
        auto min = min_element(known_nodes.begin(), known_nodes.end(),
                               [](const map_value &l, const map_value &r) { return l.second.first < r.second.first; });
        auto p_min = min->second.second;
        if (p_min->isSite) {
            if (find(top_k.begin(), top_k.end(), p_min->id) == top_k.end()) return false;
            if (++count == k) return true;
        }
        auto d_min = min->second.first;
        searched.insert(p_min->id);
        known_nodes.erase(min);
        for (auto &n: p_min->roads) {
            auto pn = shared_ptr<Node>(n->to);
            if (find(ins.begin(), ins.end(), pn->id) == ins.end()) continue;
            if (searched.find(pn->id) != searched.end()) continue;
            auto m = known_nodes.find(pn->id);
            if (m == known_nodes.end())
                known_nodes[pn->id] = make_pair(d_min + n->distance, pn);
            else if (m->second.first > d_min + n->distance)
                m->second.first = d_min + n->distance;
        }
    }
    return false;
}
