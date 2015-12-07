//
// Created by chiewen on 2015/12/6.
//


#include <gtest/gtest.h>
#include "../src/network/Node.h"
#include "../src/network/Trajectory.h"
#include "../src/algorithm/INS.h"
#include "../src/network/RoadNetwork.h"
#include "../src/algorithm/VStar.h"
#include "../src/network/TrajectoryConstructor.h"
#include "../src/util/TimePrinter.h"

void execute(const vector<PNode> &nodes, int length, int k, int x, int step){
    vector<Trajectory> trajectories;
    trajectories.reserve(10);
//    cout << "\n============= experiment start at " << TimePrinter::now << " =============" << endl;
    for (int i = 0; i < 100000; i += 20000)
        trajectories.emplace_back(TrajectoryConstructor::construct_random(nodes[i], length, step));
    cout << "random " << TimePrinter::now << "\t";

    for (int i = 0; i < 100000; i += 20000)
        trajectories.emplace_back(TrajectoryConstructor::construct_shortest_path(nodes[i], length, step));
    cout << "directed " << TimePrinter::now << "\t";

    vector<shared_ptr<VStar>> vs;
    vs.reserve(10);
    for (int i = 0; i < 10; ++i)
        vs.emplace_back(make_shared<VStar>(k, x));

    vector<shared_ptr<INS>> ins;
    for (int i = 0; i < 10; ++i)
        ins.emplace_back(make_shared<INS>(k));

    cout << "moving  " << TimePrinter::now << "\t";
    for (int i = 0; i < 10; ++i)
        vs[i]->move(trajectories[i]);
    for (int i = 0; i < 10; ++i)
        ins[i]->move(trajectories[i]);

    cout << "VS random:\t"
    << accumulate(vs.begin(), vs.begin() + 5, 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_page(); }) / 5 << "\t"
    << accumulate(vs.begin(), vs.begin() + 5, 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_server(); }) / 5 << "\t"
    << accumulate(vs.begin(), vs.begin() + 5, 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_client(); }) / 5 << "\t"
    << accumulate(vs.begin(), vs.begin() + 5, 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_communication(); }) / 5 << "\t"
    << "VS directed:\t"
    << accumulate(vs.begin() + 5, vs.end(), 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_page(); }) / 5 << "\t"
    << accumulate(vs.begin() + 5, vs.end(), 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_server(); }) / 5 << "\t"
    << accumulate(vs.begin() + 5, vs.end(), 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_client(); }) / 5 << "\t"
    << accumulate(vs.begin() + 5, vs.end(), 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_communication(); }) / 5 << "\t"
    << "INS random:\t"
    << accumulate(ins.begin(), ins.begin() + 5, 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_page(); }) / 5 << "\t"
    << accumulate(ins.begin(), ins.begin() + 5, 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_server(); }) / 5 << "\t"
    << accumulate(ins.begin(), ins.begin() + 5, 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_client(); }) / 5 << "\t"
    << accumulate(ins.begin(), ins.begin() + 5, 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_communication(); }) / 5 << "\t"
    << "INS directed:\t"
    << accumulate(ins.begin() + 5, ins.end(), 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_page(); }) / 5 << "\t"
    << accumulate(ins.begin() + 5, ins.end(), 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_server(); }) / 5 << "\t"
    << accumulate(ins.begin() + 5, ins.end(), 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_client(); }) / 5 << "\t"
    << accumulate(ins.begin() + 5, ins.end(), 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_communication(); }) / 5 << "\t"
    << endl;
}

void execute(const vector<PNode> &nodes, vector<Trajectory> &trajectories, int k, int x, int step){

    for (auto &t: trajectories)
        t.setStep(step);

    vector<shared_ptr<VStar>> vs;
    vs.reserve(20);
    for (int i = 0; i < 20; ++i)
        vs.emplace_back(make_shared<VStar>(k, x));

    vector<shared_ptr<INS>> ins;
    ins.reserve(20);
    for (int i = 0; i < 20; ++i)
        ins.emplace_back(make_shared<INS>(k));

    cout << "moving  " << TimePrinter::now << "\t";
    for (int i = 0; i < 20; ++i)
        vs[i]->move(trajectories[i]);
    for (int i = 0; i < 20; ++i)
        ins[i]->move(trajectories[i]);

    cout << "VS random:\t"
    << accumulate(vs.begin(), vs.begin() + 10, 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_page(); }) / 10 << "\t"
    << accumulate(vs.begin(), vs.begin() + 10, 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_server(); }) / 10 << "\t"
    << accumulate(vs.begin(), vs.begin() + 10, 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_client(); }) / 10 << "\t"
    << accumulate(vs.begin(), vs.begin() + 10, 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_communication(); }) / 10 << "\t"
    << "VS directed:\t"
    << accumulate(vs.begin() + 10, vs.end(), 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_page(); }) / 10 << "\t"
    << accumulate(vs.begin() + 10, vs.end(), 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_server(); }) / 10 << "\t"
    << accumulate(vs.begin() + 10, vs.end(), 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_client(); }) / 10 << "\t"
    << accumulate(vs.begin() + 10, vs.end(), 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_communication(); }) / 10 << "\t"
    << "INS random:\t"
    << accumulate(ins.begin(), ins.begin() + 10, 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_page(); }) / 10 << "\t"
    << accumulate(ins.begin(), ins.begin() + 10, 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_server(); }) / 10 << "\t"
    << accumulate(ins.begin(), ins.begin() + 10, 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_client(); }) / 10 << "\t"
    << accumulate(ins.begin(), ins.begin() + 10, 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_communication(); }) / 10 << "\t"
    << "INS directed:\t"
    << accumulate(ins.begin() + 10, ins.end(), 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_page(); }) / 10 << "\t"
    << accumulate(ins.begin() + 10, ins.end(), 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_server(); }) / 10 << "\t"
    << accumulate(ins.begin() + 10, ins.end(), 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_client(); }) / 10 << "\t"
    << accumulate(ins.begin() + 10, ins.end(), 0,
                  [](long s, const shared_ptr<MknnProcessor> &ptr) { return s + ptr->num_communication(); }) / 10 << "\t"
    << endl;
}
TEST(Experiment, First) {
    auto &nodes = RoadNetwork::get_mutable_instance();

    int length = 500;
    int k = 10;
    int x = 6;
    int step = 50;

    vector<Trajectory> trajectories;
    trajectories.reserve(20);
    cout << "\n============= experiment start at " << TimePrinter::now << " =============" << endl;
    for (int i = 0; i < 100000; i += 10000)
        trajectories.emplace_back(TrajectoryConstructor::construct_random(nodes[i], length, step));
    cout << "random " << TimePrinter::now << "\t";

    for (int i = 0; i < 100000; i += 10000)
        trajectories.emplace_back(TrajectoryConstructor::construct_shortest_path(nodes[i], length, step));
    cout << "directed " << TimePrinter::now << "\t";

//    cout << endl << "k = 1 to 20" << endl;
//    for (int i = 1; i < 20; i++)
//        execute(nodes, trajectories, i, x, step);

    cout << endl << "x = 5 to 20" << endl;
    for (int i = 1; i < 20; i++)
        execute(nodes, trajectories, k, i, step);

    cout << endl << "step = 50 to 200" << endl;
    for (int i = 50; i < 200; i += 10)
        execute(nodes, trajectories, k, x, i);

}
