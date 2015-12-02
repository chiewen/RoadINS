//
// Created by chiewen on 2015/11/13.
//

#ifndef ROADINS_MKNN_H
#define ROADINS_MKNN_H


#include "../network/Trajectory.h"
#include "MknnProcessor.h"

class INS : public MknnProcessor {
    int k;
    set<long> top_k, ins;
    set<PNode, ptr_node_less> ptr_top_k;
public:
    INS(int k) : k(k) { }

    void move(Trajectory trajectory);

    void refresh(int k, set<long> &top_k, set<PNode, ptr_node_less> &ptr_top_k, set<long> &ins,
                 const pair<PRoad, double> &pos);
};


#endif //ROADINS_MKNN_H
