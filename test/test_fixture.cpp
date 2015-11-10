//
// Created by chiewen on 2015/11/10.
//

#include "test_fixture.h"

void NodesNetTest::SetUp() {
    const string new_york_data = "D:\\work\\Data\\New York City\\USA-road-d.NY";
    const string usa_data = "D:\\work\\Data\\Full USA\\USA-road-d.USA";
    const string central_data = "D:\\work\\Data\\Central USA\\USA-road-d.CTR";

    nodes = DataReader::read_data(new_york_data);

    cout << "nodes num: " << nodes.size() << endl;

    long roads = accumulate(nodes.begin(), nodes.end(), 0, [](long sum, const shared_ptr<Node> &node) {
        return sum + node->roads.size();
    });

    cout << "roads num: " << roads << endl;
}