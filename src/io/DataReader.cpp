//
// Created by chiewen on 2015/11/7.
//
#include <iostream>
#include <fstream>
#include <regex>
#include <thread>
#include <future>

#include "DataReader.h"
#include "../util/TimePrinter.h"
#include "boost/timer/timer.hpp"

using namespace std;

vector<PNode> DataReader::read_data(const string &name, long length) {
    vector<PNode> all_nodes;
    read_nodes(name, all_nodes, length);
    read_roads(name, all_nodes);
    return all_nodes;
}

void DataReader::read_nodes(const string &name, vector<PNode> &all_nodes, long length) {
    boost::timer::cpu_timer timer;

//    cout << endl << "start reading node file from " << name << ".co   " << TimePrinter::now << endl;
    vector<string> vec_lines = read_file(name + ".co");

//    cout << "file reading finished at " << TimePrinter::now << " now parsing..." << endl;
    auto thread_num = thread::hardware_concurrency();
    long node_length = length == 0 ? (long)vec_lines.size() : length;
    auto block_size = node_length / thread_num;
    regex reg_node("v (\\d*) (-?\\d*) (\\d*)");
    auto construct_nodes = [&](long s, long t) -> vector<PNode> {
        vector<PNode> nodes;
        smatch m;
        for (int i = s; i < t; i++) {
            if (regex_search(vec_lines[i].cbegin(), vec_lines[i].cend(), m, reg_node))
                nodes.push_back(make_shared<Node>(stol(m.str(1)), stod(m.str(2)), stod(m.str(3))));
        }
        return nodes;
    };

    vector<future<vector<PNode>>> vec_future;
    for (long i = 0; i < thread_num - 1; i++)
        vec_future.push_back(async(launch::async, construct_nodes, block_size * i, block_size * (i + 1)));
    auto nodes = construct_nodes(block_size * (thread_num - 1), node_length);
    for (auto &f: vec_future) {
        auto v = f.get();
        all_nodes.insert(all_nodes.end(), v.begin(), v.end());
    }
    all_nodes.insert(all_nodes.end(), nodes.begin(), nodes.end());

//    cout << "nodes finished." << TimePrinter::now << "\t" << timer.format() << endl;
}

vector<string> DataReader::read_file(const string &name) {
    vector<string> vec_lines;
    string line;
    ifstream node_file(name);
    for (int i = 0; i < 7; i++) getline(node_file, line);
    while (getline(node_file, line)) vec_lines.push_back(line);
    node_file.close();
    return vec_lines;
}

void DataReader::read_roads(const string &name, vector<PNode> &all_nodes) {
    boost::timer::cpu_timer timer;

//    cout << endl << "start reading road file from " << name << ".gr  " << TimePrinter::now << endl;
    vector<string> vec_lines = read_file(name + ".gr");

//    cout << "file reading finished at " << TimePrinter::now << " now parsing..." << endl;

    auto thread_num = thread::hardware_concurrency();
    auto block_size = vec_lines.size() / thread_num;
    regex reg_road("a (\\d*) (\\d*) (\\d*)");
    auto insert_road = [&](long s, long t) {
        smatch m;
        for (long i = s; i < t; i++) {
            if (regex_search(vec_lines[i].cbegin(), vec_lines[i].cend(), m, reg_road)) {
                auto a1 = lower_bound(all_nodes.begin(), all_nodes.end(), make_shared<Node>(stol(m.str(1)), 0, 0),
                                      [](const PNode &a, const PNode &b) {
                                          return a->id < b->id;
                                      });
                auto a2 = lower_bound(all_nodes.begin(), all_nodes.end(), make_shared<Node>(stol(m.str(2)), 0, 0),
                                      [](const PNode &a, const PNode &b) {
                                          return a->id < b->id;
                                      });
                if (a1 != all_nodes.end() && a2 != all_nodes.end()) {
                    //we use the dataset as undirected graph
                    if (find_if((*a1)->roads.begin(), (*a1)->roads.end(), [&a2](const PRoad &r) {
                        return r->to.lock()->id == (*a2)->id;
                    }) != (*a1)->roads.end())
                        continue;
                    auto road = make_shared<Road>(*a1, *a2, stod(m.str(3)));
                    {
                        lock_guard<mutex> {(*a1)->mutex_roads};
                        (*a1)->roads.push_back(road);
                    }
                    auto road1 = make_shared<Road>(*a2, *a1, stod(m.str(3)));
                    lock_guard<mutex> {(*a2)->mutex_roads};
                    (*a2)->roads.push_back(road1);
                }
            }
        }
    };
    vector<thread> vec_threads;
    for (int i = 0; i < thread_num - 1; i++)
        vec_threads.emplace_back(insert_road, block_size * i, block_size * (i + 1));
    insert_road(block_size * (thread_num - 1), vec_lines.size());
    for_each(vec_threads.begin(), vec_threads.end(), mem_fn(&thread::join));
//    cout << "finish reading roads " << TimePrinter::now << "\t" << timer.format() << endl;
}
