//
// Created by chiewen on 2015/11/10.
//

#ifndef ROADINS_DIRECTIONALTRAJECTORYCONSTRUCTOR_H
#define ROADINS_DIRECTIONALTRAJECTORYCONSTRUCTOR_H


#include "Trajectory.h"

class RandomTrajectoryConstructor {
public:
    static Trajectory construct(shared_ptr<Node> source_node, int roads_count);

};


#endif //ROADINS_DIRECTIONALTRAJECTORYCONSTRUCTOR_H
