//
// Created by chiewen on 2015/11/10.
//

#include <gtest/gtest.h>
#include <boost/timer/timer.hpp>
#include "../src/network/Node.h"
#include "../src/network/Trajectory.h"
#include "test_fixture.h"
#include "../src/algorithm/INS.h"
#include "../src/network/RoadNetwork.h"
#include "../src/algorithm/VStar.h"
#include "../src/network/TrajectoryConstructor.h"
#include "../src/util/TimePrinter.h"

TEST(Trajectory, Simple) {
    auto n0 = make_shared<Node>(0, 0, 0);
    auto n1 = make_shared<Node>(1, 0, 0);
    auto n2 = make_shared<Node>(2, 0, 0);

    vector<PRoad> roads;
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

    auto path2 = TrajectoryConstructor::construct_random(nodes[100], 500, 50);
    cout << "path 2 " << path2.road_count() << endl;
    auto path1 = TrajectoryConstructor::construct_shortest_path(
            nodes[0], 500, 50);
    cout << "path 1 " << path1.road_count() << endl;

    {
        VStar vs(10, 6);
        cout << "VS " << TimePrinter::now << endl;
        boost::timer::cpu_timer timer;
        vs.move(path1);
        cout << "VS\ntimer: " << timer.format();
        cout << "page:" << vs.num_page() << endl;
        cout << "server:" << vs.num_server() << endl;
        cout << "client:" << vs.num_client() << endl;
        cout << "communication:" << vs.num_communication() << endl;
        cout << "total step:" << vs.total_step << endl << endl;
        cout << "VS" << TimePrinter::now << endl;

        INS ins(10);
        cout << "INS " << TimePrinter::now << endl;
        boost::timer::cpu_timer timer1;
        ins.move(path1);
        cout << "INS\ntimer: " << timer1.format();
        cout << "page:" << ins.num_page() << endl;
        cout << "server:" << ins.num_server() << endl;
        cout << "client:" << ins.num_client() << endl;
        cout << "communication:" << ins.num_communication() << endl;
        cout << "total step:" << ins.total_step << endl << endl;
    }
    {
        VStar vs(10, 6);
        cout << "VS " << TimePrinter::now << endl;
        boost::timer::cpu_timer timer;
        vs.move(path2);
        cout << "VS\ntimer: " << timer.format();
        cout << "page:" << vs.num_page() << endl;
        cout << "server:" << vs.num_server() << endl;
        cout << "client:" << vs.num_client() << endl;
        cout << "communication:" << vs.num_communication() << endl;
        cout << "total step:" << vs.total_step << endl << endl;

        INS ins(10);
        cout << "INS " << TimePrinter::now << endl;
        boost::timer::cpu_timer timer1;
        ins.move(path2);
        cout << "INS\ntimer: " << timer1.format();
        cout << "page:" << ins.num_page() << endl;
        cout << "server:" << ins.num_server() << endl;
        cout << "client:" << ins.num_client() << endl;
        cout << "communication:" << ins.num_communication() << endl;
        cout << "total step:" << ins.total_step << endl << endl;
    }
}