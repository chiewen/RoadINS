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
    static vector<shared_ptr<Node>> read_data(const string &name);

};


#endif //ROADINS_DATAREADER_H
