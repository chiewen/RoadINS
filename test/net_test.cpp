//
// Created by Chiewen on 2015/11/6.
//
#include <numeric>
#include <iostream>
#include <algorithm>

#include "gtest/gtest.h"
#include "../src/network/Node.h"
#include "../src/io/DataReader.h"
#include "../src/algorithm/Dijkstra.h"

TEST(Network, Node) {

    const string new_york_data = "D:\\work\\Data\\New York City\\USA-road-d.NY";
    const string usa_data = "D:\\work\\Data\\Full USA\\USA-road-d.USA";
    const string central_data = "D:\\work\\Data\\Central USA\\USA-road-d.CTR";

    vector<shared_ptr<Node>> nodes = DataReader::read_data(new_york_data);

    cout << "nodes num: " << nodes.size() << endl;

    long roads = accumulate(nodes.begin(), nodes.end(), 0, [](long sum, const shared_ptr<Node> &node) {
        return sum + node->roads.size();
    });

    cout << "roads num: " << roads << endl;

    DataReader::addSites(nodes, 0.1);

    DataReader::calc_dijkstra(nodes);

    ASSERT_EQ(1, 1);
}


