//
// Created by Chiewen on 2015/11/16.
//

#include <regex>
#include <iostream>
#include "RoadNetwork.h"

#include "boost/core/ignore_unused.hpp"

RoadNetwork::_init RoadNetwork::__init;

RoadNetwork::_init::_init() {
    boost::ignore_unused(__init);
    reset();
}

void RoadNetwork::reset() {
    const string new_york_data = "D:\\work\\Data\\New York City\\USA-road-d.NY";
    const string usa_data = "D:\\work\\Data\\Full USA\\USA-road-d.USA";
    const string central_data = "D:\\work\\Data\\Central USA\\USA-road-d.CTR";

    vector<shared_ptr<Node>> nodes;
    nodes = DataReader::read_data(new_york_data);
    cout << "nodes num: " << nodes.size() << endl;

    long roads = accumulate(nodes.begin(), nodes.end(), 0, [](long sum, const shared_ptr<Node> &node) {
        return sum + node->roads.size();
    });
    cout << "roads num: " << roads << endl;

    addSites(nodes, 0.07);
    get_mutable_instance().swap(nodes);
}

void RoadNetwork::addSites(const vector<shared_ptr<Node>> &nodes, double ratio) {
    double sum = 0;
    long i = 1;
    for (auto n: nodes) {
        sum += ratio;
        if (sum > i) {
            i++;
            n->isSite = true;
        }
    }
}