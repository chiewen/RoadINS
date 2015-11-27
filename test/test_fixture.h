//
// Created by chiewen on 2015/11/10.
//

#ifndef ROADINS_TEST_FIXTURE_H
#define ROADINS_TEST_FIXTURE_H

#include <gtest/gtest.h>
#include "../src/network/Node.h"
#include "../src/io/DataReader.h"
#include "../src/util/ptr_node_comp.h"

class NodesNetTest : public ::testing::Test {
protected:
    vector<PNode> nodes;

    virtual void SetUp();
};

#endif //ROADINS_TEST_FIXTURE_H
