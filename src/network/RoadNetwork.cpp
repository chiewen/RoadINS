//
// Created by Chiewen on 2015/11/16.
//

#include <regex>
#include <iostream>
#include <thread>
#include "RoadNetwork.h"
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/xml_parser.hpp"
#include "boost/core/ignore_unused.hpp"
#include "../algorithm/Dijkstra.h"
#include "../util/TimePrinter.h"
#include "boost/timer/timer.hpp"

RoadNetwork::_init RoadNetwork::__init;

RoadNetwork::_init::_init() {
    boost::ignore_unused(__init);
    reset();
}

void RoadNetwork::reset() {
    using namespace boost::property_tree;
    ptree pt;
    read_xml("D:\\work\\Code\\RoadINS\\conf.xml", pt);
    const string file_path = pt.get<string>("conf.file_path");
    const double ratio = pt.get<double>("conf.site_ratio");

    vector<PNode> nodes = DataReader::read_data(file_path);
    cout << "nodes num: " << nodes.size() << endl;
    cout << "roads num: " << accumulate(nodes.begin(), nodes.end(), 0, [](long sum, const PNode &node) {
        return sum + node->roads.size();
    }) << endl;

    add_sites(nodes, ratio);
    set_nearest(nodes);
    get_mutable_instance().swap(nodes);
}

void RoadNetwork::add_sites(const vector<PNode> &nodes, double ratio) {
    double sum = 0;
    long i = 1;
    for (auto &n: nodes) {
        sum += ratio;
        if (sum > i) {
            i++;
            n->isSite = true;
        }
    }
}

void RoadNetwork::set_nearest(const vector<PNode> &nodes) {
    boost::timer::cpu_timer timer;
    auto thread_num = thread::hardware_concurrency();
    auto block_size = nodes.size() / thread_num;
    auto calc_dijkstra_block = [&](long s, long t) {
        for (long i = s; i < t; i++) Dijkstra::find_nearest(nodes[i]);
    };

    cout << "start calculating nearest neighbors_with_road " << TimePrinter::now << endl;
    vector<thread> threads_nearest;
    for (int i = 0; i < thread_num - 1; i++)
        threads_nearest.emplace_back(calc_dijkstra_block, block_size * i, block_size * (i + 1));
    calc_dijkstra_block(block_size * (thread_num - 1), nodes.size());
    for_each(threads_nearest.begin(), threads_nearest.end(), mem_fn(&thread::join));

    cout << "finish calculating nearest neighbors_with_road. calculaing voronoi neighbors..." << TimePrinter::now <<
    endl;
    auto calc_voronoi = [&](long s, long t) {
        for (long i = s; i < t; i++) {
            for (auto &r: nodes[i]->roads)
                if (r->from.lock()->nearest_site.first.lock()->id != r->to.lock()->nearest_site.first.lock()->id) {
                    lock_guard<mutex> {r->from.lock()->nearest_site.first.lock()->mutex_voronoi};
                    r->from.lock()->nearest_site.first.lock()->voronoi_neighbors.insert(
                            r->to.lock()->nearest_site.first.lock()->id);
                }
        }
    };
    vector<thread> threads_voronoi;
    for (int i = 0; i < thread_num - 1; i++)
        threads_voronoi.emplace_back(calc_voronoi, block_size * i, block_size * (i + 1));
    calc_voronoi(block_size * (thread_num - 1), nodes.size());
    for_each(threads_voronoi.begin(), threads_voronoi.end(), mem_fn(&thread::join));
    cout << "finish calculating voronoi neighbors.\t" << timer.format() << endl;
}
