/***********************
* shon wolf
* 208581660
* 8921004
* project_part_2
**********************/
#include "EmpiricalExperiment.h"

/****************************************************************************************************
* function name: doExperiment.
* The Input: string filename.
* The output: nothing.
* The Function operation: this function do experiment on the graphs in the file "graphs.txt" and
*                         write the solutions to "solutions.txt".
****************************************************************************************************/
void EmpiricalExperiment::doExperiment() {
    fstream fs, fs1;
    fs.open("graphs.txt", fstream::in | fstream::out | fstream::app);
    if (fs.fail()) {
        __throw_runtime_error("there was error in opening to the file");
    }
    // if empty there is no solution yet to take
    if (fs.peek() == EOF) {
        return;
    }
    remove("solutions.txt");
    fs1.open("solutions.txt", fstream::in | fstream::out | fstream::app);
    if (fs1.fail()) {
        __throw_runtime_error("there was error in opening to the file");
    }
    string line;
    int numberOfMatrix;
    getline(fs, line);
    // first line is the number of matrix
    numberOfMatrix = stoi(line);
    // move on all the matrix
    for (int i = 1; i <= numberOfMatrix; i++) {
        getline(fs, line);
        // read the empty lines
        while (line == "" || line == "\r" || line == "\n" || line == "\t") {
            getline(fs, line);
        }
        int graphSize = stoi(line);
        vector<pair<int, int>> indexes = {};
        // first take the enterIndexes and the exitIndexes
        for (int j = 1; j <= 2; j++) {
            getline(fs, line);
            int endPos = line.find(",");
            string x1 = line.substr(0, endPos);
            this->eraseSpaces(x1);
            line = line.substr(endPos + 1, line.length());
            string x2 = line;
            this->eraseSpaces(x2);
            indexes.push_back(pair<int, int>(stoi(x1), stoi(x2)));
        }
        // take the enter to matrix indexes (i, j)
        pair<int, int> enterIndexes(indexes[0].first, indexes[0].second);
        pair<int, int> exitIndexes(indexes[1].first, indexes[1].second);
        vector<vector<string>> matrix = {};
        string row;
        // create the matrix
        for (int k = 1; k <= graphSize; k++) {
            // every line is another row in the matrix
            getline(fs, row);
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
        }
        // the matrix of States
        NeighborsMatrix<string>* nm;
        int pathPrice;
        int numberOfNodesEvaluated;
        string solution = "";

        // the matrix of States
        nm = new NeighborsMatrix<string>(enterIndexes, exitIndexes, matrix);
        // for Best First Search
        BestFirstSearch<string>* bestFirstSearch = new BestFirstSearch<string>();
        list<State<string>*> bestFirstSearchPath = bestFirstSearch->search(nm);
        pathPrice = 0;
        for (auto &curState : bestFirstSearchPath) {
            pathPrice += curState->getCost();
        }
        if (bestFirstSearchPath.empty()) {
            pathPrice = -1;
        }
        numberOfNodesEvaluated = bestFirstSearch->getNumberOfNodesEvaluated();
        delete(nm);
        solution = to_string(pathPrice) + "," + to_string(numberOfNodesEvaluated);
        fs1 << solution << "\n";


        // the matrix of States
        nm = new NeighborsMatrix<string>(enterIndexes, exitIndexes, matrix);
        // for Depth First Search
        DepthFirstSearch<string>* depthFirstSearch = new DepthFirstSearch<string>();
        list<State<string>*> depthFirstSearchPath = depthFirstSearch->search(nm);
        pathPrice = 0;
        for (auto &curState : depthFirstSearchPath) {
            pathPrice += curState->getCost();
        }
        if (depthFirstSearchPath.empty()) {
            pathPrice = -1;
        }
        numberOfNodesEvaluated = depthFirstSearch->getNumberOfNodesEvaluated();
        delete(nm);
        solution = to_string(pathPrice) + "," + to_string(numberOfNodesEvaluated);
        fs1 << solution << "\n";



        // the matrix of States
        nm = new NeighborsMatrix<string>(enterIndexes, exitIndexes, matrix);
        // for Breadth First Search
        BreadthFirstSearch<string>* breadthFirstSearch = new BreadthFirstSearch<string>();
        list<State<string>*> breadthFirstSearchPath = breadthFirstSearch->search(nm);
        pathPrice = 0;
        for (auto &curState : breadthFirstSearchPath) {
            pathPrice += curState->getCost();
        }
        if (breadthFirstSearchPath.empty()) {
            pathPrice = -1;
        }
        numberOfNodesEvaluated = breadthFirstSearch->getNumberOfNodesEvaluated();
        delete(nm);
        solution = to_string(pathPrice) + "," + to_string(numberOfNodesEvaluated);
        fs1 << solution << "\n";



        // the matrix of States
        nm = new NeighborsMatrix<string>(enterIndexes, exitIndexes, matrix);
        // for A Star Search
        AStar<string>* aStar = new AStar<string>();
        list<State<string>*> aStarPath = aStar->search(nm);
        pathPrice = 0;
        for (auto &curState : aStarPath) {
            pathPrice += curState->getCost();
        }
        if (aStarPath.empty()) {
            pathPrice = -1;
        }
        numberOfNodesEvaluated = aStar->getNumberOfNodesEvaluated();
        delete(nm);
        solution = to_string(pathPrice) + "," + to_string(numberOfNodesEvaluated);
        fs1 << solution << "\n";


        delete(bestFirstSearch);
        delete(depthFirstSearch);
        delete(breadthFirstSearch);
        delete(aStar);
    }
    fs.close();
    if (fs.is_open()) {
        __throw_runtime_error("there was error in closing to the file");
    }
    fs1.close();
    if (fs.is_open()) {
        __throw_runtime_error("there was error in closing to the file");
    }
}

/****************************************************************************************************
   * function name: eraseSpaces.
   * The Input: string val.
   * The output: nothing.
   * The Function operation: this function erase the spaces before or after the string that she gets.
   ****************************************************************************************************/
void EmpiricalExperiment::eraseSpaces(string& val) {
    // erase the spaces before the string
    while (val.front() == ' ') {
        val = val.substr(1, val.length());
    }
    // erase the spaces after the string
    while (val.back() == ' ') {
        val = val.substr(0, val.length() - 1);
    }
}