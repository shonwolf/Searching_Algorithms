/***********************
* shon wolf
* 208581660
* 8921004
* project_part_2
**********************/
#ifndef FILECACHEMANAGER_H
#define FILECACHEMANAGER_H

#include "CacheManager.h"
#include <unordered_map>
#include <fstream>
#include <string>
#include "Parser.h"
#include <mutex>
using std::mutex;
mutex mtx;
template<class Problem, class Solution> class FileCacheManager : public CacheManager<Problem, Solution> {
    // the members
    unordered_map<string, Solution> m_solutions;
    Parser<Problem, Solution>* m_parser;
    string m_filename;
public:

    /****************************************************************************************************
    * function name: this is constructor.
    * The Input: Parser<Problem, Solution>* parser, string filename.
    * The output: nothing.
    * The Function operation: initialize the members with the data.
    *****************************************************************************************************/
    FileCacheManager(Parser<Problem, Solution>* parser, string filename) {
        this->m_solutions = {};
        this->m_parser = parser;
        this->m_filename = filename;
        int endPos = 0;
        fstream fs;
        fs.open(filename, fstream::in | fstream::out | fstream::app);
        if (fs.fail()) {
            __throw_runtime_error("there was error in opening to the file");
        }
        // if empty there is no solution yet to take
        if (fs.peek() == EOF) {
            return;
        }
        string line;
        string p;
        Solution s;
        // get the solutions to the problems
        while (getline(fs, line)) {
            endPos = line.find("   $   ");
            p = line.substr(0, endPos);
            line = line.substr(endPos + 7, line.length());
            s = this->m_parser->parseStringToSolution(line, p);
            // save the problem and the solution in the map
            this->m_solutions.emplace(p, s);
        }
        fs.close();
        if (fs.is_open()) {
            __throw_runtime_error("there was error in closing to the file");
        }
    }

    /****************************************************************************************************
    * function name: doesHasSolutionToProblem.
    * The Input: string p.
    * The output: true if the solution for this problem as already solved and we got it, false otherwise.
    * The Function operation: this function checks in the map of the solution if we already got the
    *                         solution to the problem, and return true if we do, false otherwise.
    *****************************************************************************************************/
    virtual bool doesHasSolutionToProblem(Problem p) {
        string problemAsString = this->m_parser->parseProblemToString(p);
        mtx.lock();
        if (this->m_solutions.count(problemAsString)) {
            mtx.unlock();
            return true;
        }
        mtx.unlock();
        return false;
    }

    /****************************************************************************************************
    * function name: getSolutionToProblem.
    * The Input: string p.
    * The output: the solution to that problem.
    * The Function operation: this function return the solution to that problem.
    *****************************************************************************************************/
    virtual Solution getSolutionToProblem(Problem p) {
        string problemAsString = this->m_parser->parseProblemToString(p);
        // if we do not have the solution to that problem, throw exception
        if (!this->doesHasSolutionToProblem(p)) {
            __throw_invalid_argument("this Problem does not have Solution");
        }
        mtx.lock();
        Solution temp = this->m_solutions[problemAsString];
        mtx.unlock();
        return temp;
    }

    /****************************************************************************************************
    * function name: saveSolutionForProblem.
    * The Input: string p, string s.
    * The output: nothing.
    * The Function operation: this function saves the solution to the problem.
    *****************************************************************************************************/
    virtual void saveSolutionForProblem(Problem p, Solution s) {
        string problemAsString = this->m_parser->parseProblemToString(p);
        mtx.lock();
        this->m_solutions.emplace(problemAsString, s);
        mtx.unlock();
    }

    /****************************************************************************************************
    * function name: ~FileCacheManager.
    * The Input: nothing.
    * The output: nothing.
    * The Function operation: the destructor make sure to erase all the things that were put on the
    *                         heap.
    ****************************************************************************************************/
    ~FileCacheManager() {
        string line;
        remove(this->m_filename.c_str());
        fstream fs;
        fs.open(this->m_filename, fstream::in | fstream::out | fstream::app);
        if (fs.fail()) {
            __throw_runtime_error("there was error in opening to the file");
        }
        // save all the solutions from the unordered_map into a file - in format of problem   $   solution
        for (auto &curSolution : this->m_solutions) {
            // the format to represent the problem and the solution in the file
            line = curSolution.first + "   $   " + this->m_parser->parseSolutionToString(curSolution.second);
            // add to the file
            fs << line << "\n";
        }
        fs.close();
        if (fs.is_open()) {
            __throw_runtime_error("there was error in closing to the file");
        }
    }
};

#endif
