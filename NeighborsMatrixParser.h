/***********************
* shon wolf
* 208581660
* 8921004
* project_part_2
**********************/
#ifndef NEIGHBORSMATRIXPARSER_H
#define NEIGHBORSMATRIXPARSER_H

#include "Parser.h"
#include "NeighborsMatrix.h"
template<class T> class NeighborsMatrixParser : public Parser<Searchable<T>*, list<State<T>*>> {
    // the members
    list<State<T>*> states;

    /****************************************************************************************************
    * function name: CreateMatrixFromString.
    * The Input: string matrixInString.
    * The output: the matrix from the string.
    * The Function operation: this function return the matrix from the string.
    ****************************************************************************************************/
    vector<vector<string>> CreateMatrixFromString(string matrixInString) {
        vector<vector<string>> matrix = {};
        int endPos = 0;
        while (!matrixInString.empty()) {
            vector<string> rowOfVals = {};
            endPos = matrixInString.find(";");
            string row = matrixInString.substr(0, endPos);
            while (row.find(",") != string::npos) {
                int endPos = row.find(",");
                string val = row.substr(0, endPos);
                rowOfVals.push_back(val);
                // erase the first val from the row because we took him to the matrix already
                row = row.substr(endPos + 1, row.length());
            }
            // the last val
            rowOfVals.push_back(row);
            // add the rowOfVals to the matrix
            matrix.push_back(rowOfVals);
            matrixInString = matrixInString.substr(endPos + 1, matrixInString.length());
        }
        return matrix;
    }
public:

    /****************************************************************************************************
    * function name: this is constructor.
    * The Input: Parser<Problem, Solution>* parser, string filename.
    * The output: nothing.
    * The Function operation: initialize the members with the data.
    *****************************************************************************************************/
    NeighborsMatrixParser() {
        this->states = {};
    }

    /****************************************************************************************************
    * function name: parseProblemToString.
    * The Input: Searchable<T>* p, the Problem to parse to string.
    * The output: the parsed solution.
    * The Function operation: this function parse the solution to string.
    ****************************************************************************************************/
    virtual string parseProblemToString(Searchable<T>* p) {
        string representationOfMatrixInString = "";
        for (auto &curRow : dynamic_cast<NeighborsMatrix<T>*>(p)->getMatrix()) {
            for (auto &curVal : curRow) {
                representationOfMatrixInString += curVal + ",";
            }
            // remove the last ","
            representationOfMatrixInString.pop_back();
            // show the end of a row in the matrix
            representationOfMatrixInString += ";";
        }
        // add the two indexes that represent the start indexes and the end indexes of the searching
        representationOfMatrixInString += to_string(p->getInitialState()->getStateIndexes().first) + ","
                                          + to_string(p->getInitialState()->getStateIndexes().second);
        representationOfMatrixInString += ";";
        representationOfMatrixInString += to_string(p->getGoalState()->getStateIndexes().first) + ","
                                          + to_string(p->getGoalState()->getStateIndexes().second);
        representationOfMatrixInString += ";";
        return representationOfMatrixInString;
    }

    /****************************************************************************************************
    * function name: parseSolutionToString.
    * The Input: string s, the Solution to parse to string.
    * The output: the parsed solution.
    * The Function operation: this function parse the solution to string.
    ****************************************************************************************************/
    virtual string parseSolutionToString(list<State<T>*> s) {
        if (s.empty()) {
            return "";
        }
        string solutionInStringRepresentation = "";
        list<State<T>*> copy = s;

        /*
         * move on all the states and get the direction by checking every time if the next state is
         * (Up/Down/Left/Right) from the current state.
         */
        while (!copy.empty()) {
            State<T>* cur = copy.front();
            copy.pop_front();
            if (copy.empty()) {
                break;
            }
            State<T>* next = copy.front();
            if (next->getStateIndexes().first < cur->getStateIndexes().first) {
                solutionInStringRepresentation += "Up";
            } else if (next->getStateIndexes().first > cur->getStateIndexes().first) {
                solutionInStringRepresentation += "Down";
            } else if (next->getStateIndexes().second < cur->getStateIndexes().second) {
                solutionInStringRepresentation += "Left";
            } else {
                solutionInStringRepresentation += "Right";
            }
            solutionInStringRepresentation += ",";
        }
        // ignore the last "," was added
        solutionInStringRepresentation.pop_back();
        return solutionInStringRepresentation;
    }

    /****************************************************************************************************
    * function name: parseStringToSolution.
    * The Input: string solutionAsString, , string matrixInString.
    * The output: the parsed string.
    * The Function operation: this function parse the string to solution.
    ****************************************************************************************************/
    virtual list<State<T>*> parseStringToSolution(string solutionAsString, string matrixInString) {
        vector<vector<string>> matrix = CreateMatrixFromString(matrixInString);
        /* the two last vectors contain the startIndexes and the exitIndexes */
        // don't need the exitIndexes
        matrix.pop_back();
        int i = stoi(matrix.back()[0]);
        int j = stoi(matrix.back()[1]);
        // remove the startIndexes - need to stay only with the matrix now
        matrix.pop_back();
        list<State<T>*> solution = {};
        int valIndex = 0;
        State<T>* start = new State<T>("v" + to_string(valIndex), stod(matrix[i][j]), pair<int, int>(i,j));
        this->states.push_back(start);
        solution.push_back(start);
        valIndex++;
        // create the states for the Solution
        while (solutionAsString.find(",") != string::npos) {
            int endPos = solutionAsString.find(",");
            string direction = solutionAsString.substr(0, endPos);
            // get the stateIndexes
            if (direction == "Up") {
                // j is the same
                i = i - 1;
            } else if (direction == "Down") {
                // j is the same
                i = i + 1;
            } else if (direction == "Left") {
                // i is the same
                j = j - 1;
            } else {
                // i is the same
                j = j + 1;
            }
            State<T>* state = new State<T>("v" + to_string(valIndex), stod(matrix[i][j]), pair<int, int>(i, j));
            this->states.push_back(state);
            solution.push_back(state);
            valIndex++;
            // erase the first val from the row because we took him to the matrix already
            solutionAsString = solutionAsString.substr(endPos + 1, solutionAsString.length());
        }
        // add the last state
        // get the stateIndexes
        if (solutionAsString == "Up") {
            // j is the same
            i = i - 1;
        } else if (solutionAsString == "Down") {
            // j is the same
            i = i + 1;
        } else if (solutionAsString == "Left") {
            // i is the same
            j = j - 1;
        } else {
            // i is the same
            j = j + 1;
        }
        State<T>* end = new State<T>("v" + to_string(valIndex), stod(matrix[i][j]), pair<int, int>(i, j));
        this->states.push_back(end);
        solution.push_back(end);
        return solution;
    }

    /****************************************************************************************************
    * function name: ~NeighborsMatrix.
    * The Input: nothing.
    * The output: nothing.
    * The Function operation: the destructor make sure to erase all the things that were put on the
    *                         heap.
    ****************************************************************************************************/
    ~NeighborsMatrixParser() {
        for (auto &curState : this->states) {
            delete(curState);
        }
    }
};

#endif
