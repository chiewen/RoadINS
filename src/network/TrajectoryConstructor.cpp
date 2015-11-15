//
// Created by chiewen on 2015/11/10.
//
#include <set>
#include <algorithm>
#include "TrajectoryConstructor.h"

#include "Node.h"
#include "../algorithm/Dijkstra.h"

using namespace std;

Trajectory TrajectoryConstructor::construct_random(
        shared_ptr<Node> source_node, int roads_count) {
    vector<shared_ptr<Road>> roads;
    set<long> already_have;
    shared_ptr<Node> current_node(source_node);
    for (; roads.size() < roads_count;) {
        auto next_road = find_if(current_node->roads.begin(), current_node->roads.end(),
                                 [&](const shared_ptr<Road> &ptr) {
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
    return Trajectory(roads);
}

Trajectory TrajectoryConstructor::construct_shortest_path(shared_ptr<Node> source_node,
                                                          shared_ptr<Node> destination_node) {
    return Trajectory(Dijkstra::shortest_path(source_node, destination_node));
}
