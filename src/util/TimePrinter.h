//
// Created by chiewen on 2015/11/7.
//

#ifndef ROADINS_TIMEPRINTER_H
#define ROADINS_TIMEPRINTER_H

#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

struct TimePrinter {
    static TimePrinter now;
};

ostream& operator << (ostream &out, const TimePrinter &timePrinter);

#endif //ROADINS_TIMEPRINTER_H
