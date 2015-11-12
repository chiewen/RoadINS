//
// Created by chiewen on 2015/11/10.
//
#include <numeric>

#include "Trajectory.h"

Trajectory::Trajectory(const vector<shared_ptr<Road>> &roads, double step) : roads(roads), step(step) {
    current_road = this->roads.begin();
    dist_from = 0.0;
}

bool Trajectory::has_next() {
    return current_road != roads.end();
}

pair<shared_ptr<Road>, double> Trajectory::get_current_and_step_forward() {
    auto result = make_pair(*current_road, dist_from);
    if (dist_from + step <= (*current_road)->distance)
        dist_from += step;
    else {
        dist_from = dist_from + step - (*current_road)->distance;
        advance(current_road, 1);
        while (has_next() && dist_from > (*current_road)->distance) {
            dist_from -= (*current_road)->distance;
            advance(current_road, 1);
        }
    }
    return result;
}

double Trajectory::getStep() const {
    return step;
}

void Trajectory::setStep(double step) {
    Trajectory::step = step;
}

double Trajectory::total_distance() {
    return accumulate(roads.begin(), roads.end(), 0.0, [](double sum, const weak_ptr<Road> &ptr){
        return sum + ptr.lock()->distance;
    });
}

Trajectory::roads_type::difference_type Trajectory::road_count() {
    return roads.size();
}
