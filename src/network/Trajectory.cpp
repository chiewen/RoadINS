//
// Created by chiewen on 2015/11/10.
//
#include <numeric>
#include "Node.h"
#include "Trajectory.h"

Trajectory::Trajectory(const vector<PRoad> &roads, double step) : roads(roads), step(step) {
    current_road = this->roads.begin();
    if (current_road != roads.end())
        dist_to = (*current_road)->distance;
}

bool Trajectory::has_next() {
    return current_road != roads.end();
}

pair<PRoad, double> Trajectory::get_then_forward() {
    auto result = make_pair(*current_road, dist_to);
    if (dist_to > step) dist_to -= step;
    else {
        double dist_from = step - dist_to;
        advance(current_road, 1);
        while (has_next() && dist_from > (*current_road)->distance) {
            dist_from -= (*current_road)->distance;
            advance(current_road, 1);
        }
        dist_to = current_road != roads.end() ? (*current_road)->distance - dist_from : numeric_limits<double>::max();
    }
    return result;
}

double Trajectory::getStep() const {
    return step;
}

void Trajectory::setStep(double step) {
    this->step = step;
}

double Trajectory::total_distance() {
    return accumulate(roads.begin(), roads.end(), 0.0, [](double sum, const weak_ptr<Road> &ptr) {
        return sum + ptr.lock()->distance;
    });
}

Trajectory::roads_type::difference_type Trajectory::road_count() {
    return roads.size();
}
