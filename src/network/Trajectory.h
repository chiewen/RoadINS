//
// Created by chiewen on 2015/11/10.
//

#ifndef ROADINS_TRAJECTORY_H
#define ROADINS_TRAJECTORY_H

#include <memory>

#include "Road.h"

using namespace std;

class Trajectory {
private:
    double step;
    vector<shared_ptr<Road>> roads;
    vector<shared_ptr<Road>>::iterator current_road;
    double dist_from;

public:
    Trajectory(const vector<shared_ptr<Road>> &roads, double step = 50);

    pair<shared_ptr<Road>, double> get_current_and_step_forward();

    long road_count();

    bool has_next();

    double total_distance();

    double getStep() const;

    void setStep(double step);
};


#endif //ROADINS_TRAJECTORY_H
