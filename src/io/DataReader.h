//
// Created by chiewen on 2015/11/7.
//

#ifndef ROADINS_DATAREADER_H
#define ROADINS_DATAREADER_H

#include <vector>
#include <string>

#include "../network/Node.h"
#include "../network/Road.h"

using namespace std;

class DataReader {
public:
    static vector<PNode> read_data(const string &name, long length = 0);
private:
    static void read_nodes(const string &name, vector<PNode> &all_nodes, long length = 0);
    static void read_roads(const string &name, vector<PNode> &all_nodes);
    static vector<string> read_file(const string &name);
};


#endif //ROADINS_DATAREADER_H
