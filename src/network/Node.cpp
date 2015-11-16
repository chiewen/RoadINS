//
// Created by chiewen on 2015/11/7.
//

#include "Node.h"
#include "Road.h"
#include "../util/ptr_node_comp.h"

using namespace std;

Node::Node(long id, double x, double y) : id(id), x(x), y(y) { }

vector<pair<shared_ptr<Node>, shared_ptr<Road>>> Node::neighbors_with_road() {
    vector<pair<shared_ptr<Node>, shared_ptr<Road>>> vec_neighbors;
    for (auto r: roads) vec_neighbors.emplace_back(r->to.lock(), r);
    return vec_neighbors;
}

vector<shared_ptr<Node>> Node::neighbors() {
    vector<shared_ptr<Node>> vec_neighbors;
    for (auto r: roads) vec_neighbors.push_back(r->to.lock());
    return vec_neighbors;
}