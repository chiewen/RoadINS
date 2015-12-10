//
// Created by chiewen on 2015/12/10.
//

#include <gtest/gtest.h>
#include <thread>
#include "../src/network/Node.h"
#include "../src/network/Trajectory.h"
#include "../src/algorithm/INS.h"
#include "../src/network/RoadNetwork.h"
#include "../src/algorithm/VStar.h"
#include "../src/network/TrajectoryConstructor.h"
#include "../src/util/TimePrinter.h"

typedef typename vector<shared_ptr<MknnProcessor>>::iterator MPIter;

void print_result(string name, MPIter start, MPIter end) {
    vector<long> v_page, v_server, v_client, v_communication;
    for (auto &p = start; p != end; p++) {
        v_page.push_back((*p)->num_page());
        v_server.push_back((*p)->num_server());
        v_client.push_back((*p)->num_client());
        v_communication.push_back((*p)->num_communication());
    }

    sort(v_page.begin(), v_page.end());
    sort(v_server.begin(), v_server.end());
    sort(v_client.begin(), v_client.end());
    sort(v_communication.begin(), v_communication.end());

    cout << name << ":\t"
    << accumulate(v_page.begin() + 4, v_page.begin() + 8, 0) / 4 << "\t"
    << accumulate(v_server.begin() + 4, v_server.begin() + 8, 0) / 4 << "\t"
    << accumulate(v_client.begin() + 4, v_client.begin() + 8, 0) / 4 << "\t"
    << accumulate(v_communication.begin() + 4, v_communication.begin() + 8, 0) / 4 << "\t";
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

    vector<shared_ptr<MknnProcessor>> mps;
    mps.reserve(48);
    for (int i = 0; i < 24; ++i)
        mps.emplace_back(make_shared<VStar>(k, x));
    for (int i = 0; i < 24; ++i)
        mps.emplace_back(make_shared<INS>(k));

    vector<thread> vt;
    vt.reserve(12);
    for (int j = 0; j < 4; ++j) {
        for (int i = 12 * j; i < 12 * (j + 1); i++)
            vt.emplace_back([&mps, i, &trajectories]() {
                mps[i]->move(trajectories[i]);
            });
        for (auto &t : vt) t.join();
        vt.clear();
    }

    print_result("VR", mps.begin(), mps.begin() + 12);
    print_result("VD", mps.begin() + 12, mps.begin() + 24);
    print_result("IR", mps.begin() + 24, mps.begin() + 36);
    print_result("ID", mps.begin() + 36, mps.end());
    cout << endl;
}

TEST(Experiment, Multi) {
    auto &nodes = RoadNetwork::get_mutable_instance();

    int length = 500;
    int k = 10;
    int x = 6;
    int step = 40;

    vector<Trajectory> trajectories;
    trajectories.reserve(48);
    cout << "\n============= experiment start at " << TimePrinter::now << " =============\n" << endl;
    for (int i = 0; i < 120000; i += 40000) {
        auto traj = TrajectoryConstructor::construct_random(nodes[i], length, step);
        trajectories.emplace_back(traj);
        trajectories.emplace_back(traj);
        trajectories.emplace_back(traj);
        trajectories.emplace_back(traj);
    }

    cout << "R " << TimePrinter::now << endl;

    vector<thread> vt;
    mutex m_traj;
    for (int i = 0; i < 120000; i += 40000)
        vt.emplace_back([i, length, step, &m_traj, &trajectories, &nodes]() {
            auto t = TrajectoryConstructor::construct_shortest_path(nodes[i], length, step);
            lock_guard<mutex> {m_traj};
            trajectories.push_back(t);
            trajectories.push_back(t);
            trajectories.push_back(t);
            trajectories.push_back(t);
        });

    for (auto &t : vt)
        t.join();

    cout << "D " << TimePrinter::now << endl;

    copy(trajectories.begin(), trajectories.begin() + 24, back_inserter(trajectories));

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
