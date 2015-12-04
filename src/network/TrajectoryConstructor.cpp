//
// Created by chiewen on 2015/11/10.
//
#include <iostream>
#include <set>
#include <algorithm>
#include "TrajectoryConstructor.h"

#include "../algorithm/Dijkstra.h"

using namespace std;

Trajectory TrajectoryConstructor::construct_random(
        const PNode &source_node, int roads_count, int step) {
    vector<PRoad> roads;
    set<long> already_have;
    PNode current_node(source_node);
    for (; roads.size() < roads_count;) {
        auto next_road = find_if(current_node->roads.begin(), current_node->roads.end(),
                                 [&](const PRoad &ptr) {
                                     return already_have.find(ptr->to.lock()->id) == already_have.end();
                                 });
        already_have.insert(current_node->id);
        if (next_road == current_node->roads.end()) {
            current_node = roads.back()->from.lock();
            roads.pop_back();
        }
        else {
            roads.emplace_back(*next_road);
            current_node = (*next_road)->to.lock();
        }
    }

    return Trajectory(roads, step);
}

Trajectory TrajectoryConstructor::construct_shortest_path(const PNode &source_node,
                                                          long length, int step) {
    return Trajectory(Dijkstra::shortest_path_length(source_node, length), step);
}
