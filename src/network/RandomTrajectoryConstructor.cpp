//
// Created by chiewen on 2015/11/10.
//
#include <set>
#include <algorithm>
#include "RandomTrajectoryConstructor.h"

#include "Node.h"

using namespace std;

Trajectory RandomTrajectoryConstructor::construct(
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
