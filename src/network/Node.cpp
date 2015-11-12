//
// Created by chiewen on 2015/11/7.
//

#include "Node.h"
#include "Road.h"

using namespace std;

Node::Node(long id, double x, double y) : id(id), x(x), y(y) { }

vector<pair<shared_ptr<Node>, shared_ptr<Road>>> Node::neighbors() {
    vector<pair<shared_ptr<Node>, shared_ptr<Road>>> vec_neighbors;
    for (auto r: roads) vec_neighbors.emplace_back(r->to, r);
    return vec_neighbors;
}
