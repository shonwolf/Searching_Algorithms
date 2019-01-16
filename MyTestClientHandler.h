/***********************
* shon wolf
* 208581660
* 8921004
* project_part_2
**********************/
#ifndef MYTESTCLIENTHANDLER_H
#define MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
#include <string>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include "Parser.h"
template<class Problem, class Solution> class MyTestClientHandler : public ClientHandler {
    // the members
    Solver<Problem, Solution>* m_solver;
    CacheManager<Problem, Solution>* m_cm;
    Parser<Problem, Solution>* m_parser;
public:

    /****************************************************************************************************
    * function name: this is constructor.
    * The Input: Solver<Problem, Solution>* solver, CacheManager<Problem, Solution>* cm,
                 Parser<Problem, Solution>* parser..
    * The output: nothing.
    * The Function operation: initialize the members with the data.
    ****************************************************************************************************/
    MyTestClientHandler(Solver<Problem, Solution>* solver, CacheManager<Problem, Solution>* cm,
                        Parser<Problem, Solution>* parser) {
        this->m_solver = solver;
        this->m_cm = cm;
        this->m_parser = parser;
    }

    /****************************************************************************************************
    * function name: handleClient.
    * The Input: int sockfd.
    * The output: nothing.
    * The Function operation: this function talk to the clients and give solutions to their problems.
    ****************************************************************************************************/
    virtual void handleClient(int sockfd) {
        // read the messages from the client and right him messages back
        while(true) {
            char buffer[1024];
            int  n;
            // if connection is established then start communicating
            bzero(buffer,1024);
            timeval timeout;
            timeout.tv_sec = 0;
            timeout.tv_usec = 0;
            setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
            n = read(sockfd, buffer, 1023);
            if (n < 0) {
                perror("ERROR reading from socket");
                exit(1);
            }
            // remove the "\r\n" from the end
            buffer[strlen(buffer) - 2] = '\0';
            /* the message is inside the buffer now */
            // if the client entered "end", we stop talking to him
            if (strcmp(buffer, "end") == 0) {
                return;
            }
            string solutionAsString;
            const char* solutionToSendClient;
            Solution s;

            /*
             * if we have the solution to the problem than send it, and if we do not, we solve the problem, than save
             * the solution and than send it.
             */
            if (this->m_cm->doesHasSolutionToProblem(buffer)) {
                s = this->m_cm->getSolutionToProblem(buffer);
                solutionAsString = this->m_parser->parseSolutionToString(s);
                solutionAsString += "\r\n";
                solutionToSendClient = solutionAsString.c_str();
            } else {
                s = this->m_solver->solve(buffer);
                solutionAsString = this->m_parser->parseSolutionToString(s);
                solutionAsString += "\r\n";
                solutionToSendClient = solutionAsString.c_str();
                this->m_cm->saveSolutionForProblem(buffer, s);
            }
            // write a response to the client - solution of the problem, send is write to the client and does flush too
            n = send(sockfd, solutionToSendClient, strlen(solutionToSendClient), 0);
            if (n < 0) {
                perror("ERROR writing to socket");
                exit(1);
            }
        }
    }
    ~MyTestClientHandler() {}
};

#endif

