//
// Created by chiewen on 2015/11/24.
//

#ifndef ROADINS_MKNNPROCESSOR_H
#define ROADINS_MKNNPROCESSOR_H

#include <chrono>
#include "../network/Trajectory.h"

using namespace std;

class MknnProcessor {
    chrono::steady_clock::time_point start_time_server;
    chrono::steady_clock::time_point start_time_client;
    chrono::steady_clock::duration duration_server;
    chrono::steady_clock::duration duration_client;
protected:
    MknnProcessor() : total_step(0), communication(0), page(0),
                      duration_server(chrono::steady_clock::duration()),
                      duration_client(chrono::steady_clock::duration()) { }

    long communication;
    long page;

    void server_start() { start_time_server = chrono::steady_clock::now(); }

    void server_pause() { duration_server += chrono::steady_clock::now() - start_time_server; }

    void client_start() { start_time_client = chrono::steady_clock::now(); }

    void client_pause() { duration_client += chrono::steady_clock::now() - start_time_client; }

    void client_to_server() {
        client_pause();
        server_start();
    }

    void server_to_client() {
        server_pause();
        client_start();
    }

public:
    long total_step;

    long num_server() { return (long) chrono::duration_cast<chrono::milliseconds>(duration_server).count(); }

    long num_client() { return (long) chrono::duration_cast<chrono::milliseconds>(duration_client).count(); }

    long num_page() { return page; }

    long num_communication() { return communication; }

    virtual void move(Trajectory trajectory) = 0;
};


#endif //ROADINS_MKNNPROCESSOR_H
