//
// Created by chiewen on 2015/11/7.
//
#include <map>
#include <set>
#include <algorithm>
#include <iostream>

#include "Dijkstra.h"

using namespace std;

void Dijkstra::find_nearest(const PNode &ptr_node) {
    known_map known_nodes;
    known_nodes[ptr_node->id] = make_pair(0.0, ptr_node);

    typedef vector<pair<PNode, double>> neighbor_vec;
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
        for (auto &n: p_min->roads) {
            auto pn = PNode(n->to);
            if (searched.find(pn->id) != searched.end()) continue;
            auto m = known_nodes.find(pn->id);
            if (m == known_nodes.end())
                known_nodes[pn->id] = make_pair(d_min + n->distance, pn);
            else if (m->second.first > d_min + n->distance)
                m->second.first = d_min + n->distance;
        }
    }
}


void Dijkstra::top_k(const PNode &ptr_node, double dist_to_node, int k,
                     set<long> &top_k, set<PNode, ptr_node_less> &ptr_top_k) {
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
        for (auto &n: p_min->roads) {
            auto pn = PNode(n->to);
            if (searched.find(pn->id) != searched.end()) continue;
            auto m = known_nodes.find(pn->id);
            if (m == known_nodes.end())
                known_nodes[pn->id] = make_pair(d_min + n->distance, pn);
            else if (m->second.first > d_min + n->distance)
                m->second.first = d_min + n->distance;
        }
    }
    top_k.clear();
    transform(ptr_top_k.begin(), ptr_top_k.end(), inserter(top_k, top_k.begin()),
              [](const PNode &n) { return n->id; });
}

vector<PRoad> Dijkstra::shortest_path(const PNode &ptr_from, const PNode &ptr_to) {
    vector<PRoad> result;
    map<long, tuple<double, PNode, PRoad>> known_nodes;
    known_nodes.insert(make_pair(ptr_from->id, make_tuple(0, ptr_from, nullptr)));
    map<long, PRoad> searched;
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
            for (auto &n: p_min->roads) {
                auto pn = PNode(n->to);
                if (searched.find(pn->id) != searched.end()) continue;
                auto m = known_nodes.find(pn->id);
                if (m == known_nodes.end())
                    known_nodes.insert(make_pair(pn->id, make_tuple(d_min + n->distance, pn, n)));
                else if (get<0>(m->second) > d_min + n->distance) {
                    get<0>(m->second) = d_min + n->distance;
                    get<2>(m->second) = n;
                }
            }
    }
    return result;
}

bool Dijkstra::verify(int k, const PNode &query_object, double dist_to_next,
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
            auto pn = PNode(n->to);
            auto nearest_id = pn->nearest_site.first.lock()->id;
            if (ins.find(nearest_id) == ins.end() && top_k.find(nearest_id) == top_k.end()) continue;
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
