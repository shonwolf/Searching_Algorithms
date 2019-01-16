/***********************
* shon wolf
* 208581660
* 8921004
* project_part_2
**********************/
#ifndef MYPARALLEL_H
#define MYPARALLEL_H

#include "Server.h"
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <thread>
#include <queue>
using namespace server_side;
using std::thread;
using std::queue;
using std::move;
class MyParallelServer : public Server {
    void start(int sockfd, ClientHandler* ch);
    void callHandleClientOnNewThread(ClientHandler* ch, int sockfd);
public:
    virtual void open(int port, ClientHandler* ch);
    virtual void stop(int sockfd);
    ~MyParallelServer() {}
};

#endif
