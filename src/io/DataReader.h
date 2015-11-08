//
// Created by chiewen on 2015/11/7.
//

#ifndef ROADINS_DATAREADER_H
#define ROADINS_DATAREADER_H

#include <vector>
#include <string>

#include "../network/Node.h"
#include "../network/Road.h"
#include "../util/ctpl_stl.h"

using namespace std;

class DataReader {
private:
    static ctpl::thread_pool pool;
public:
    static vector<shared_ptr<Node>> read_data(const string &name);
    static void addSites(const vector<shared_ptr<Node>> &nodes, double ratio);
    static void calc_dijkstra(const vector<shared_ptr<Node>> & nodes);
private:
    static void read_nodes(const string &name, vector<shared_ptr<Node>> &all_nodes);
    static void read_roads(const string &name, vector<shared_ptr<Node>> &all_nodes);
    static vector<string> read_file(const string &name);
};


#endif //ROADINS_DATAREADER_H
