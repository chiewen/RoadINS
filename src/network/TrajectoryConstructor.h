//
// Created by chiewen on 2015/11/10.
//

#ifndef ROADINS_DIRECTIONALTRAJECTORYCONSTRUCTOR_H
#define ROADINS_DIRECTIONALTRAJECTORYCONSTRUCTOR_H


#include "Trajectory.h"

struct TrajectoryConstructor {
    static Trajectory construct_random(PNode source_node, int roads_count);
    static Trajectory construct_shortest_path(PNode source_node, PNode destination_node);

};


#endif //ROADINS_DIRECTIONALTRAJECTORYCONSTRUCTOR_H
