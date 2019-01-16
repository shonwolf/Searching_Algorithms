/***********************
* shon wolf
* 208581660
* 8921004
* project_part_2
**********************/
#ifndef SERVER_H
#define SERVER_H

namespace server_side {

#include "ClientHandler.h"
    class Server {
    public:
        virtual void open(int port, ClientHandler* ch) = 0;
        virtual void stop(int sockfd) = 0;
        virtual ~Server() {}
    };

}

#endif
