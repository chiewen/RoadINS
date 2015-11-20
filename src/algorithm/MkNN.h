//
// Created by chiewen on 2015/11/13.
//

#ifndef ROADINS_MKNN_H
#define ROADINS_MKNN_H


#include "../network/Trajectory.h"

struct MkNN {
    static void move(Trajectory trajectory, int k);

    static void refresh(int k, set<long> &top_k,  set<weak_ptr<Node>, ptr_node_less> &ptr_top_k, set<long> &ins,
                        const pair<shared_ptr<Road>, double> &pos);
};


#endif //ROADINS_MKNN_H
