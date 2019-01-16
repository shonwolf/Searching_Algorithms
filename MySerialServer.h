/***********************
* shon wolf
* 208581660
* 8921004
* project_part_2
**********************/
#ifndef MYSERIALSERVER_H
#define MYSERIALSERVER_H

#include "Server.h"
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <thread>
using namespace server_side;
using namespace std;
class MySerialServer : public Server {
    void start(int sockfd, ClientHandler* ch);
public:
    virtual void open(int port, ClientHandler* ch);
    virtual void stop(int sockfd);
    ~MySerialServer() {}
};

#endif
