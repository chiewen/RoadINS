//
// Created by chiewen on 2015/11/24.
//

#ifndef ROADINS_VSTAR_H
#define ROADINS_VSTAR_H

#include "MknnProcessor.h"

using namespace std;

class VStar: public MknnProcessor {
private:
    int x;
public:
    VStar(int x);
    void move(Trajectory trajectory, int k);
};


#endif //ROADINS_VSTAR_H