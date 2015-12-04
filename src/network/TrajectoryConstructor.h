//
// Created by chiewen on 2015/11/10.
//

#ifndef ROADINS_DIRECTIONALTRAJECTORYCONSTRUCTOR_H
#define ROADINS_DIRECTIONALTRAJECTORYCONSTRUCTOR_H


#include "Trajectory.h"

struct TrajectoryConstructor {
    static Trajectory construct_random(const PNode &source_node, int roads_count, int step);
    static Trajectory construct_shortest_path(const PNode &source_node, long length, int step);

};


#endif //ROADINS_DIRECTIONALTRAJECTORYCONSTRUCTOR_H
