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
#include "test_fixture.h"


TEST_F(NodesNetTest, Node) {
    DataReader::addSites(nodes, 0.1);
    DataReader::calc_dijkstra(nodes);
    ASSERT_EQ(1, 1);
}


