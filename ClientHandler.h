/***********************
* shon wolf
* 208581660
* 8921004
* project_part_2
**********************/
#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

class ClientHandler {
public:
    virtual void handleClient(int sockfd) = 0;
    virtual ~ClientHandler() {}
};

#endif
