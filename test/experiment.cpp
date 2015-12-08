//
// Created by chiewen on 2015/12/6.
//


#include <gtest/gtest.h>
#include <thread>
#include <functional>
#include <algorithm>
#include "../src/network/Node.h"
#include "../src/network/Trajectory.h"
#include "../src/algorithm/INS.h"
#include "../src/network/RoadNetwork.h"
#include "../src/algorithm/VStar.h"
#include "../src/network/TrajectoryConstructor.h"
#include "../src/util/TimePrinter.h"

using namespace std::placeholders;


typedef typename vector<shared_ptr<MknnProcessor>>::iterator MPIter;

void print_result(string name, MPIter start, MPIter end) {
    cout << name <<":\t"
    << accumulate(start, end, 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_page(); }) / 5 << "\t"
    << accumulate(start, end, 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_server(); }) / 5 << "\t"
    << accumulate(start, end, 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_client(); }) / 5 << "\t"
    << accumulate(start, end, 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_communication(); }) / 5 <<
    "\t";
}

void execute(const vector<PNode> &nodes, int length, int k, int x, int step) {
    vector<Trajectory> trajectories;
    trajectories.reserve(10);
//    cout << "\n============= experiment start at " << TimePrinter::now << " =============" << endl;
    for (int i = 0; i < 100000; i += 20000)
        trajectories.emplace_back(TrajectoryConstructor::construct_random(nodes[i], length, step));
    cout << "R " << TimePrinter::now << "\t";

    for (int i = 0; i < 100000; i += 20000)
        trajectories.emplace_back(TrajectoryConstructor::construct_shortest_path(nodes[i], length, step));
    cout << "D " << TimePrinter::now << "\t";

    vector<shared_ptr<MknnProcessor>> vs;
    vs.reserve(10);
    for (int i = 0; i < 10; ++i)
        vs.emplace_back(make_shared<VStar>(k, x));

    vector<shared_ptr<MknnProcessor>> ins;
    for (int i = 0; i < 10; ++i)
        ins.emplace_back(make_shared<INS>(k));

    cout << "moving  " << TimePrinter::now << "\t";
    for (int i = 0; i < 10; ++i)
        vs[i]->move(trajectories[i]);
    for (int i = 0; i < 10; ++i)
        ins[i]->move(trajectories[i]);

    print_result("VR", vs.begin(), vs.begin() + 5);
    print_result("VD", vs.begin() + 5, vs.end());
    print_result("IR", ins.begin(), ins.begin() + 5);
    print_result("ID", ins.begin() + 5, ins.end());
    cout << endl;
}


void execute(const vector<PNode> &nodes, vector<Trajectory> &trajectories, int k, int x, int step) {
    for (auto &t: trajectories)
        t.setStep(step);

    vector<shared_ptr<MknnProcessor>> vs;
    vs.reserve(10);
    for (int i = 0; i < 10; ++i)
        vs.emplace_back(make_shared<VStar>(k, x));

    vector<shared_ptr<MknnProcessor>> ins;
    ins.reserve(10);
    for (int i = 0; i < 10; ++i)
        ins.emplace_back(make_shared<INS>(k));

    vector<thread> vt;
    for (int i = 0; i < 10; ++i)
        vt.emplace_back([&vs, i, &trajectories]() {
            vs[i]->move(trajectories[i]);
        });

    vt.clear();

    for (int i = 0; i < 10; ++i)
        vt.emplace_back([&ins, i, &trajectories]() {
            ins[i]->move(trajectories[i]);
        });

    for (auto &t : vt)
        t.join();

    print_result("VR", vs.begin(), vs.begin() + 5);
    print_result("VD", vs.begin() + 5, vs.end());
    print_result("IR", ins.begin(), ins.begin() + 5);
    print_result("ID", ins.begin() + 5, ins.end());
    cout << endl;
}

TEST(Experiment, First) {
    auto &nodes = RoadNetwork::get_mutable_instance();

    int length = 500;
    int k = 10;
    int x = 6;
    int step = 100;

    vector<Trajectory> trajectories;
    trajectories.reserve(10);
    cout << "\n============= experiment start at " << TimePrinter::now << " =============\n" << endl;
    for (int i = 0; i < 100000; i += 20000)
        trajectories.emplace_back(TrajectoryConstructor::construct_random(nodes[i], length, step));

    cout << "R " << TimePrinter::now << endl;

    vector<thread> vt;
    mutex m_traj;
    for (int i = 0; i < 100000; i += 20000)
        vt.emplace_back([i, length, step, &m_traj, &trajectories, &nodes]() {
            auto t = TrajectoryConstructor::construct_shortest_path(nodes[i], length, step);
            lock_guard<mutex> {m_traj};
            trajectories.push_back(t);
        });

    for (auto &t : vt)
        t.join();

    cout << "D " << TimePrinter::now << endl;

//    cout << endl << "k = 1 to 20" << endl;
//    for (int i = 1; i < 20; i++)
//        execute(nodes, trajectories, i, x, step);

//    cout << endl << "x = 5 to 20" << endl;
//    for (int i = 1; i < 20; i++)
//        execute(nodes, trajectories, k, i, step);

    cout << endl << "step = 50 to 2000 step 50" << endl;
    for (int i = 50; i < 1000; i += 25)
        execute(nodes, trajectories, k, x, i);

    cout << endl << "ratio = 0.25 to 5 step 0.25" << endl;
    for (double ratio = 0.05; ratio <= 0.11; ratio += 0.005) {
        RoadNetwork::reset_ratio(ratio);
        execute(nodes, trajectories, k, x, step);
    }

}
