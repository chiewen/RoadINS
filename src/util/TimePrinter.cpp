//
// Created by chiewen on 2015/11/7.
//

#include "TimePrinter.h"

TimePrinter TimePrinter::now;

ostream& operator << (ostream &out, const TimePrinter &timePrinter) {
    auto t = time(nullptr);
    out << put_time(localtime(&t), "%H:%M:%S");
    return out;
}