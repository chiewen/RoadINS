//
// Created by chiewen on 2015/11/7.
//
#include <iostream>
#include <fstream>
#include <regex>

#include "DataReader.h"

using namespace std;

vector<shared_ptr<Node>> DataReader::read_data(const string &name) {
    vector<shared_ptr<Node>> all_nodes;

    ifstream node_file(name + ".co");
    regex reg_node("v (\\d*) (-?\\d*) (\\d*)");

    smatch m;
    string line;
    while (getline(node_file, line)) {
        auto pos = line.cbegin();
        for (; regex_search(pos, line.cend(), m, reg_node); pos = m.suffix().first) {
            all_nodes.push_back(make_shared<Node>(stol(m.str(1)), stod(m.str(2)), stod(m.str(3))));
        }
    }

    node_file.close();

    ifstream road_file(name + ".gr");
    regex reg_road("a (\\d*) (\\d*) (\\d*)");

    while (getline(road_file, line)) {
        auto pos = line.cbegin();
        for (; regex_search(pos, line.cend(), m, reg_road); pos = m.suffix().first) {
            auto a1 = lower_bound(all_nodes.begin(), all_nodes.end(), make_shared<Node>(stol(m.str(1)), 0, 0),
                                    [](const shared_ptr<Node>& a, const shared_ptr<Node>& b) {
                                        return a->id < b->id;
                                    });
            auto a2 = lower_bound(all_nodes.begin(), all_nodes.end(), make_shared<Node>(stol(m.str(2)), 0, 0),
                                    [](const shared_ptr<Node>& a, const shared_ptr<Node>& b) {
                                        return a->id < b->id;
                                    });
            auto road = make_shared<Road>(*a1, *a2, stod(m.str(3)));
            (*a1)->roads.push_back(road);
            (*a2)->roads.push_back(road);
        }
    }

    road_file.close();

    return all_nodes;
}
