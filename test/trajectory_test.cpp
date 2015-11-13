//
// Created by chiewen on 2015/11/10.
//

#include <gtest/gtest.h>
#include "../src/network/Node.h"
#include "../src/network/Road.h"
#include "../src/network/Trajectory.h"
#include "../src/network/RandomTrajectoryConstructor.h"
#include "test_fixture.h"
#include "../src/algorithm/Dijkstra.h"

TEST(Trajectory, Simple) {
    auto n0 = make_shared<Node>(0, 0, 0);
    auto n1 = make_shared<Node>(1, 0, 0);
    auto n2 = make_shared<Node>(2, 0, 0);

    vector<shared_ptr<Road>> roads;
    roads.push_back(make_shared<Road>(n0, n1, 100));
    roads.push_back(make_shared<Road>(n1, n2, 120));

    Trajectory t1{move(roads), 25};

    ASSERT_EQ(t1.total_distance(), 220);

    for (int i = 0; i < 4; i++) t1.get_current_and_step_forward();

    ASSERT_EQ(t1.get_current_and_step_forward().second, 100);

    for (int i = 0; i < 4; i++) t1.get_current_and_step_forward();

    ASSERT_EQ(t1.has_next(), false);
}

//TEST_F(NodesNetTest, Construct) {
//
//    auto traj = RandomTrajectoryConstructor::construct(nodes[0], 50);
//
//    ASSERT_EQ(traj.road_count(), 50);
//
//    while (traj.has_next()) {
//        auto c = traj.get_current_and_step_forward();
//        cout << c.first->from.lock()->id << ":" << c.first->to.lock()->id
//        << "(" << c.first->distance << ")" << "-->" << c.second << endl;
//    }
//}

TEST_F(NodesNetTest, Construct) {
//    auto topk = Dijkstra::top_k(nodes[1], 0, 50);
//    cout << nodes[1]->id << ":" << nodes[1]->neighbors().size() << ":" << topk.size() << endl;
//    int i = 0;
//    for (auto &n : topk) {
//        cout << "top" << ++i << n.first->id << endl;
//    }

    auto path = Dijkstra::shortest_path(nodes[1], *find_if(nodes.begin(), nodes.end(), [](const shared_ptr<Node> &n){
        return n->id == 3660;
    }));
    for (auto r: path) {
        cout << r->from.lock()->id << "\tto\t" << r->to.lock()->id << endl;
    }
}