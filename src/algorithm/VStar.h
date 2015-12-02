//
// Created by chiewen on 2015/11/24.
//

#ifndef ROADINS_VSTAR_H
#define ROADINS_VSTAR_H

#include <map>
#include "MknnProcessor.h"

using namespace std;

class VStar : public MknnProcessor {
private:
    int k;
    int x;
    vector<PNode> ordered_k_x;
    pair<PRoad, double> q_b;
    PNode z;
    double z_dist;
    typedef map<long, map<long, double>> FrrMap;
    FrrMap frrMap;
public:
    VStar(int k, int x);

    void move(Trajectory trajectory);

    void calculate(const pair<PRoad, double> &pos);

    bool validate_knn(const pair<PRoad, double> &pos);
};


#endif //ROADINS_VSTAR_H
