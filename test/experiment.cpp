//
// Created by chiewen on 2015/12/6.
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

    cout << name << ":\t"
    << accumulate(v_page.begin(), v_page.begin() + 3, 0) / 3 << "\t"
    << accumulate(v_server.begin(), v_server.begin() + 3, 0) / 3 << "\t"
    << accumulate(v_client.begin(), v_client.begin() + 3, 0) / 3 << "\t"
    << accumulate(v_communication.begin(), v_communication.begin() + 3, 0) / 3 << "\t";
}

void execute(const vector<PNode> &nodes, vector<Trajectory> &trajectories, int k, int x, int step) {
    for (auto &t: trajectories)
        t.setStep(step);

    vector<shared_ptr<MknnProcessor>> mps;
    mps.reserve(12);
    for (int i = 0; i < 6; ++i)
        mps.emplace_back(make_shared<VStar>(k, x));
    for (int i = 0; i < 6; ++i)
        mps.emplace_back(make_shared<INS>(k));

    for (int i = 0; i < 12; i++)
        mps[i]->move(trajectories[i]);

    print_result("VR", mps.begin(), mps.begin() + 3);
    print_result("VD", mps.begin() + 3, mps.begin() + 6);
    print_result("IR", mps.begin() + 6, mps.begin() + 9);
    print_result("ID", mps.begin() + 9, mps.end());
    cout << endl;
}

TEST(Experiment, First) {
    auto &nodes = RoadNetwork::get_mutable_instance();

    int length = 500;
    int k = 10;
    int x = 6;
    int step = 40;

    vector<Trajectory> trajectories;
    trajectories.reserve(12);
    cout << "\n============= experiment start at " << TimePrinter::now << " =============\n" << endl;
    for (int i = 0; i < 1200; i += 400) {
        auto traj = TrajectoryConstructor::construct_random(nodes[i], length, step);
        trajectories.emplace_back(traj);
    }

    cout << "R " << TimePrinter::now << endl;

    vector<thread> vt;
    mutex m_traj;
    for (int i = 0; i < 1200; i += 400)
        vt.emplace_back([i, length, step, &m_traj, &trajectories, &nodes]() {
            auto t = TrajectoryConstructor::construct_shortest_path(nodes[i], length, step);
            lock_guard<mutex> {m_traj};
            trajectories.push_back(t);
        });

    for (auto &t : vt)
        t.join();

    cout << "D " << TimePrinter::now << endl;

    copy(trajectories.begin(), trajectories.begin() + 6, back_inserter(trajectories));


    for (int r = 0; r < 8; r++) {
        cout << endl << "ratio = 0.05 to 0.11 step 0.005" << endl;
        for (double ratio = 0.05; ratio <= 0.11; ratio += 0.005) {
            RoadNetwork::reset_ratio(ratio);
            execute(nodes, trajectories, k, x, step);
        }
    }
//    cout << endl << "step = 10 to 100 step 5" << endl;
//    for (int i = 10; i < 100; i += 5)
//        execute(nodes, trajectories, k, x, i);
//
//    cout << endl << "x = 1 to 10" << endl;
//    for (int i = 1; i < 20; i++)
//        execute(nodes, trajectories, k, i, step);
//
//    cout << endl << "k = 1 to 20" << endl;
//    for (int i = 1; i < 20; i++)
//        execute(nodes, trajectories, i, x, step);
}

TEST(Experiment, Cardinal) {
    int length = 100;
    int k = 10;
    int x = 6;
    int step = 40;

    for (int e = 0; e < 5; e++) {

        cout << "\n============= " << e << "th experiment start at " << TimePrinter::now << " =============\n" << endl;
        vector<Trajectory> trajectories;

        cout << endl << "cardinal 5000 to 260000 step 5000" << endl;
        for (long i = 5000; i < 260000; i += 5000) {
            RoadNetwork::reset(0, i);
            auto &nodes = RoadNetwork::get_mutable_instance();

            trajectories.clear();
            trajectories.reserve(12);
            for (int i = 0; i < 1200; i += 400) {
                auto traj = TrajectoryConstructor::construct_random(nodes[i], length, step);
                trajectories.emplace_back(traj);
            }

            vector<thread> vt;
            mutex m_traj;
            for (int i = 0; i < 1200; i += 400)
                vt.emplace_back([i, length, step, &m_traj, &trajectories, &nodes]() {
                    int j = i;
                    do {
                        while (nodes[j]->nearest_site.second < 0) j++;
                        auto t = TrajectoryConstructor::construct_shortest_path(nodes[j++], length, step);
                        if (!t.has_next()) continue;
                        else {
                            lock_guard<mutex> {m_traj};
                            trajectories.push_back(t);
                            break;
                        }
                    } while (true);
                });

            for (auto &t : vt)
                t.join();

            copy(trajectories.begin(), trajectories.begin() + 6, back_inserter(trajectories));
            execute(nodes, trajectories, k, x, step);
        }
    }
}


TEST(Experiment, Length) {
    auto &nodes = RoadNetwork::get_mutable_instance();

    int k = 10;
    int x = 6;
    int step = 40;

    cout << "\n============= experiment start at " << TimePrinter::now << " =============\n" << endl;
    vector<Trajectory> trajectories;

    for (int l = 0; l < 8; l++) {
        cout << endl << "length 50 to 1000 step 50" << endl;
        for (long length = 50; length < 850; length += 50) {
            trajectories.clear();
            trajectories.reserve(12);
            for (int j = 0; j < 12000; j += 4000) {
                auto traj = TrajectoryConstructor::construct_random(nodes[j], length, step);
                trajectories.emplace_back(traj);
            }

            vector<thread> vt;
            mutex m_traj;
            for (int k = 0; k < 12000; k += 4000)
                vt.emplace_back([k, length, step, &m_traj, &trajectories, &nodes]() {
                    int j = k;
                    do {
                        while (nodes[j]->nearest_site.second < 0) j++;
                        auto t = TrajectoryConstructor::construct_shortest_path(nodes[j++], length, step);
                        if (!t.has_next()) continue;
                        else {
                            lock_guard<mutex> {m_traj};
                            trajectories.push_back(t);
                            break;
                        }
                    } while (true);
                });

            for (auto &t : vt)
                t.join();

            copy(trajectories.begin(), trajectories.begin() + 6, back_inserter(trajectories));
            execute(nodes, trajectories, k, x, step);
        }
    }
}