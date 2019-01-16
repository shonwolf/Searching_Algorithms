/***********************
* shon wolf
* 208581660
* 8921004
* project_part_2
**********************/
#ifndef MYCLIENTHANDLER_H
#define MYCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
#include <string>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include "Parser.h"
#include <vector>
#include "NeighborsMatrix.h"
using std::vector;
template<class Problem, class Solution> class MyClientHandler : public ClientHandler {
    // the members
    Solver<Problem, Solution>* m_solver;
    CacheManager<Problem, Solution>* m_cm;
    Parser<Problem, Solution>* m_parser;

    /****************************************************************************************************
    * function name: eraseSpaces.
    * The Input: string val.
    * The output: nothing.
    * The Function operation: this function erase the spaces before or after the string that she gets.
    ****************************************************************************************************/
    void eraseSpaces(string& val) {
        // erase the spaces before the string
        while (val.front() == ' ') {
            val = val.substr(1, val.length());
        }
        // erase the spaces after the string
        while (val.back() == ' ') {
            val = val.substr(0, val.length() - 1);
        }
    }
public:

    /****************************************************************************************************
    * function name: this is constructor.
    * The Input: Solver<Problem, Solution>* solver, CacheManager<Problem, Solution>* cm,
                 Parser<Problem, Solution>* parser.
    * The output: nothing.
    * The Function operation: initialize the members with the data.
    ****************************************************************************************************/
    MyClientHandler(Solver<Problem, Solution>* solver, CacheManager<Problem, Solution>* cm,
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
        vector<vector<string>> matrix = {};
        int rowIndex = 0;
        char buffer[1024];
        int n;
        timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 0;
        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
        // read the messages from the client
        while (true) {
            // if connection is established then start communicating
            bzero(buffer, 1024);
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
                break;
            }
            string row = buffer;
            vector<string> rowOfVals = {};
            // move on the row that contain all the values for this row concat by ",", and add them to the matrix
            while (row.find(",") != string::npos) {
                int endPos = row.find(",");
                string val = row.substr(0, endPos);
                this->eraseSpaces(val);
                rowOfVals.push_back(val);
                row = row.substr(endPos + 1, row.length());
            }
            // the last val
            this->eraseSpaces(row);
            rowOfVals.push_back(row);
            // add the rowOfVals to the matrix
            matrix.push_back(rowOfVals);
            rowIndex++;
        }
        /* the last two vectors are the two that represent the enter to matrix and exit of matrix */
        // take the enter to matrix indexes (i, j)
        pair<int, int> enterIndexes(stoi(matrix[matrix.size() - 2][0]), stoi(matrix[matrix.size() - 2][1]));
        pair<int, int> exitIndexes(stoi(matrix[matrix.size() - 1][0]), stoi(matrix[matrix.size() - 1][1]));
        // remove last two vectors from the matrix because they represent only the enter and exit of the  matrix
        matrix.pop_back();
        matrix.pop_back();
        NeighborsMatrix<string>* nm = new NeighborsMatrix<string>(enterIndexes, exitIndexes, matrix);
        //string problemAsString = this->m_parser->parseProblemToString(nm);
        string solutionAsString;
        const char* solutionToSendClient;
        Solution s;

        /*
          * if we have the solution to the problem than send it, and if we do not, we solve the problem, than save
          * the solution and than send it.
          */
        if (this->m_cm->doesHasSolutionToProblem(nm)) {
            s = this->m_cm->getSolutionToProblem(nm);
            solutionAsString = this->m_parser->parseSolutionToString(s);
            solutionAsString += "\r\n";
            solutionToSendClient = solutionAsString.c_str();
        } else {
            s = this->m_solver->solve(nm);
            solutionAsString = this->m_parser->parseSolutionToString(s);
            solutionAsString += "\r\n";
            solutionToSendClient = solutionAsString.c_str();
            this->m_cm->saveSolutionForProblem(nm, s);
        }
        // write a response to the client - solution of the problem, send is write to the client and does flush too
        n = send(sockfd, solutionToSendClient, strlen(solutionToSendClient), 0);
        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }
        delete(nm);
    }
    virtual ~MyClientHandler() {}
};

#endif
