//
// Created by chiewen on 2015/11/10.
//

#ifndef ROADINS_DIRECTIONALTRAJECTORYCONSTRUCTOR_H
#define ROADINS_DIRECTIONALTRAJECTORYCONSTRUCTOR_H


#include "Trajectory.h"

struct TrajectoryConstructor {
    static Trajectory construct_random(shared_ptr<Node> source_node, int roads_count);
    static Trajectory construct_shortest_path(shared_ptr<Node> source_node, shared_ptr<Node> destination_node);

};


#endif //ROADINS_DIRECTIONALTRAJECTORYCONSTRUCTOR_H
