//
// Created by chiewen on 2015/11/24.
//

#ifndef ROADINS_MKNNPROCESSOR_H
#define ROADINS_MKNNPROCESSOR_H


#include "../network/Trajectory.h"

struct MknnProcessor {
    virtual void move(Trajectory trajectory) = 0;
};


#endif //ROADINS_MKNNPROCESSOR_H
