//
// Created by chiewen on 2015/11/10.
//

#ifndef ROADINS_TRAJECTORY_H
#define ROADINS_TRAJECTORY_H

#include <memory>
#include <vector>

#include "Road.h"

using namespace std;

class Trajectory {
public:
    typedef vector<shared_ptr<Road>> roads_type;

    Trajectory(const vector<shared_ptr<Road>> &roads, double step = 50);

    pair<shared_ptr<Road>, double> get_then_forward();

    roads_type::difference_type road_count();

    bool has_next();

    double total_distance();

    double getStep() const;

    void setStep(double step);

private:
    double step;
    roads_type roads;
    roads_type::iterator current_road;
    double dist_to;
};


#endif //ROADINS_TRAJECTORY_H
