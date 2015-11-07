//
// Created by chiewen on 2015/11/7.
//

#ifndef ROADINS_NODE_H
#define ROADINS_NODE_H

#include <vector>
#include <memory>

class Road;

class Node {
public:
    long id;
    bool isSite = false;
    double x, y;

    std::vector<std::shared_ptr<Road>> roads;

public:
    Node(long id, double x, double y);

};

#endif //ROADINS_NODE_H
