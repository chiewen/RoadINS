//
// Created by chiewen on 2015/11/6.
//

#ifndef ROADINS_NODE_H
#define ROADINS_NODE_H

#include <vector>

class Road;

class Node {
public:
    std::size_t id;
    double x, y;
    std::vector<Road> roads;

public:
    Node(double x, double y): x(x), y(y){}
};


#endif //ROADINS_NODE_H
