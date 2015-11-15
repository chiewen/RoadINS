//
// Created by chiewen on 2015/11/13.
//

#ifndef ROADINS_MKNN_H
#define ROADINS_MKNN_H


#include "../network/Trajectory.h"

struct MkNN {
    void move(Trajectory trajectory, int k);
};


#endif //ROADINS_MKNN_H
