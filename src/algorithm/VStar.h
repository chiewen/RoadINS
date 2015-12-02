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
    int x;
    vector<PNode> ordered_top_k;

    typedef map<long, vector<pair<PNode, double>>> FrrMap;
    FrrMap frrMap;
public:
    VStar(int x);

    void move(Trajectory trajectory, int k);

    void calculate(const pair<PRoad,double> &pos, int k, int x);

    bool validate_knn(const pair<PRoad, double> &pos, int k, int x);
};


#endif //ROADINS_VSTAR_H
