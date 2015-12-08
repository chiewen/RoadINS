//
// Created by Chiewen on 2015/11/6.
//
#include <iostream>
#include <algorithm>

#include "gtest/gtest.h"
#include "../src/io/DataReader.h"
#include "test_fixture.h"
#include "../src/network/Trajectory.h"
#include "../src/network/RoadNetwork.h"
#include "../src/network/TrajectoryConstructor.h"


TEST_F(NodesNetTest, Traj) {
    auto &nodes = RoadNetwork::get_mutable_instance();

    auto t = TrajectoryConstructor::construct_random(nodes[0], 500, 50);

    cout <<  to_string(t.total_distance()) << "\t" << t.road_count() << "\t" <<to_string(t.total_distance()/50)<< endl;
}


