//
// Created by chiewen on 2015/11/7.
//

#include "Node.h"
#include "Road.h"

using namespace std;

Node::Node(long id, double x, double y) : id(id), x(x), y(y) { }

vector<pair<weak_ptr<Node>, double>> Node::neighbors() {
    vector<pair<weak_ptr<Node>, double>> vec_neighbors;
    for (auto r: roads) vec_neighbors.push_back(make_pair(r->terminals.second, r->distance));

    return vec_neighbors;
}
