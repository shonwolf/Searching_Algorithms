/***********************
* shon wolf
* 208581660
* 8921004
* project_part_2
**********************/
#include "MySerialServer.h"
#define NUM_OF_PEOPLE_CAN_CONNECT_TO_SOCKET 5

/****************************************************************************************************
* function name: open.
* The Input: int port, ClientHandler ch.
* The output: nothing.
* The Function operation: this function open socket and start listening to clients.
****************************************************************************************************/
void MySerialServer::open(int port, ClientHandler* ch) {
    int sockfd, portno;
    struct sockaddr_in serv_addr;
    // first call to socket function
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }
    // initialize socket structure
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = port;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    // now bind the host address using bind call
    if (bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    /*
     * now start listening for the clients, here process will go in sleep mode and will wait for the incoming
     * connection.
     */
    listen(sockfd, NUM_OF_PEOPLE_CAN_CONNECT_TO_SOCKET);
    thread startThread(&MySerialServer::start, this, sockfd, ch);
    startThread.join();
}

/****************************************************************************************************
* function name: start.
* The Input: int sockfd, ClientHandler* ch.
* The output: nothing.
* The Function operation: this function connect to clients.
****************************************************************************************************/
void MySerialServer::start(int sockfd, ClientHandler* ch) {
    int newsockfd, clilen;
    struct sockaddr_in cli_addr;
    clilen = sizeof(cli_addr);
    timeval timeout;
    bool isFirstClient = true;
    // start accepting people in serial order
    while (true) {
        // accept actual connection from the client
        newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, (socklen_t*) &clilen);
        // if was timeout or error in the accept
        if (newsockfd < 0) {
            // if there was timeout
            if (errno == EWOULDBLOCK) {
                this->stop(newsockfd);
                break;
            } else {
                perror("ERROR on accept");
                exit(1);
            }
        }
        // call to ch->handleClient for handle with the client
        ch->handleClient(newsockfd);
        this->stop(newsockfd);
        // wait 1 second for more clients
        if (isFirstClient) {
            timeout.tv_sec = 1;
            timeout.tv_usec = 0;
            setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
            isFirstClient = false;
        }
    }
}

/****************************************************************************************************
* function name: stop.
* The Input: int sockfd.
* The output: nothing.
* The Function operation: this function close the server - the socket.
****************************************************************************************************/
void MySerialServer::stop(int sockfd) {
    close(sockfd);
}
