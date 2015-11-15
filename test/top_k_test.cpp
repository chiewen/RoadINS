//
// Created by chiewen on 2015/11/13.
//

#include "gtest/gtest.h"
#include "test_fixture.h"
#include "../src/algorithm/Dijkstra.h"

TEST_F(NodesNetTest, TopK) {
    auto topk = Dijkstra::top_k(nodes[0], 0, 5000);
    transform(topk.begin(), topk.end(), ostream_iterator<long>(cout, "\n"), [](const shared_ptr<Node> &n){
        return n->id;
    });
}