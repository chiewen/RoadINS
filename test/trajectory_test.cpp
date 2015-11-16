//
// Created by chiewen on 2015/11/10.
//

#include <gtest/gtest.h>
#include "../src/network/Node.h"
#include "../src/network/Trajectory.h"
#include "test_fixture.h"
#include "../src/algorithm/Dijkstra.h"
#include "../src/algorithm/MkNN.h"
#include "../src/network/RoadNetwork.h"

TEST(Trajectory, Simple) {
    auto n0 = make_shared<Node>(0, 0, 0);
    auto n1 = make_shared<Node>(1, 0, 0);
    auto n2 = make_shared<Node>(2, 0, 0);

    vector<shared_ptr<Road>> roads;
    roads.push_back(make_shared<Road>(n0, n1, 100));
    roads.push_back(make_shared<Road>(n1, n2, 120));

    Trajectory t1{move(roads), 25};

    ASSERT_EQ(t1.total_distance(), 220);

    for (int i = 0; i < 4; i++) t1.get_then_forward();

    ASSERT_EQ(t1.get_then_forward().second, 120);

    for (int i = 0; i < 4; i++) t1.get_then_forward();

    ASSERT_EQ(t1.has_next(), false);
}

//TEST_F(NodesNetTest, Construct) {
//
//    auto traj = TrajectoryConstructor::construct_random(nodes[0], 50);
//
//    ASSERT_EQ(traj.road_count(), 50);
//
//    while (traj.has_next()) {
//        auto c = traj.get_then_forward();
//        cout << c.first->from.lock()->id << ":" << c.first->to.lock()->id
//        << "(" << c.first->distance << ")" << "-->" << c.second << endl;
//    }
//}

TEST_F(NodesNetTest, Construct) {

    auto &nodes = RoadNetwork::get_mutable_instance();

    auto path = Dijkstra::shortest_path(nodes[0], *find_if(nodes.begin(), nodes.end(), [](const shared_ptr<Node> &n){
        return n->id == 201071;//this node is the 5000th nearest neighbor of nodes[0]
    }));
    for (auto r: path) {
        cout << r->from.lock()->id << "\tto\t" << r->to.lock()->id << endl;
    }
    cout << "total:\t" << path.size() << endl;

    MkNN::move(path, 5);
}