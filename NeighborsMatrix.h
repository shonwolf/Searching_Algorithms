/***********************
* shon wolf
* 208581660
* 8921004
* project_part_2
**********************/
#ifndef NEIGHBORSMATRIX_H
#define NEIGHBORSMATRIX_H

#include "Searchable.h"
#include <vector>
using std::vector;
using std::to_string;
template<class T> class NeighborsMatrix : public Searchable<T> {
    // the members
    State<T>* m_initialState;
    State<T>* m_goalState;
    vector<vector<string>> m_matrix;
    vector<vector<State<T>*>> m_matrixOfStates;

    /****************************************************************************************************
    * function name: createMatrixAsMatrixOfStates.
    * The Input: nothing.
    * The output: nothing.
    * The Function operation: this function add states from the values that the user entered as matrix
    *                         to the matrixOfStates.
    ****************************************************************************************************/
    void createMatrixAsMatrixOfStates() {
        int valIndex = 0;
        int rowIndex = 0;
        int colIndex= 0;
        // move on all the matrix
        for (auto &curRow : this->m_matrix) {
            vector<State<T>*> rowOfStates = {};
            // move on all the row
            for (auto &curVal : curRow) {
                // create the state, fill in with v(i), cost of the state
                State<T>* state = new State<T>("v" + to_string(valIndex), stod(curVal),
                                               pair<int, int>(rowIndex, colIndex));
                rowOfStates.push_back(state);
                valIndex++;
                colIndex++;
            }
            this->m_matrixOfStates.push_back(rowOfStates);
            rowIndex++;
            colIndex = 0;
        }
    }
public:

    /****************************************************************************************************
    * function name: this is constructor.
    * The Input: pair<int, int> enterIndexes,pair<int, int> exitIndexes, vector<vector<string>> matrix.
    * The output: nothing.
    * The Function operation: initialize the members with the data.
    ****************************************************************************************************/
    NeighborsMatrix(pair<int, int> enterIndexes, pair<int, int> exitIndexes, vector<vector<string>> matrix) {
        this->m_matrix = matrix;
        // create the matrixOfStates
        this->createMatrixAsMatrixOfStates();
        this->m_initialState = this->m_matrixOfStates[enterIndexes.first][enterIndexes.second];
        this->m_goalState = this->m_matrixOfStates[exitIndexes.first][exitIndexes.second];
    }

    /****************************************************************************************************
    * function name: getInitialState.
    * The Input: nothing.
    * The output: the initialState.
    * The Function operation: this function return the initialState.
    ****************************************************************************************************/
    virtual State<T>* getInitialState() {
        return this->m_initialState;
    }

    /****************************************************************************************************
    * function name: getGoalState.
    * The Input: nothing.
    * The output: the goalState.
    * The Function operation: this function return the goalState.
    ****************************************************************************************************/
    virtual State<T>* getGoalState() {
        return this->m_goalState;
    }

    /****************************************************************************************************
    * function name: getAllPossibleStates.
    * The Input: State<T> s.
    * The output: list of all the states that we can reach to from the state that the function gets with
    *             the directions (Up, Down, Left, Right).
    * The Function operation: this function return list of all the states that we can reach to from the
    *                         state that the function gets with the directions (Up, Down, Left, Right),
    *                         we can reach to a state if his cost is >= 0. This function also does
    *                         setCameFrom(s) for all the successors she puts in the list she returns.
    ****************************************************************************************************/
    virtual list<State<T>*> getAllPossibleStates(State<T>* s) {
        list<State<T>*> allPossibleStates = {};
        if (s->getStateIndexes().first < (int)this->m_matrixOfStates.size() - 1) {
            State<T>* down = this->m_matrixOfStates[s->getStateIndexes().first + 1][s->getStateIndexes().second];
            // check that the Down state cost >= to 0 and if it does add him to allPossibleStates - (i + 1, j) state
            if (down->getCost() >= 0) {
                allPossibleStates.push_back(down);
            }
        }
        if (s->getStateIndexes().second < (int)this->m_matrixOfStates[0].size() - 1) {
            State<T>* right = this->m_matrixOfStates[s->getStateIndexes().first][s->getStateIndexes().second + 1];
            // check that the Right state cost >= to 0 and if it does add him to allPossibleStates - (i, j + 1) state
            if (right->getCost() >= 0) {
                allPossibleStates.push_back(right);
            }
        }
        /* can put in the list only the states that s can reach to with the directions (Up, Down, Left, Right) */
        if (s->getStateIndexes().first > 0) {
            State<T>* up = this->m_matrixOfStates[s->getStateIndexes().first - 1][s->getStateIndexes().second];
            // check that the Up state cost >= to 0 and if it does add him to allPossibleStates - (i - 1, j) state
            if (up->getCost() >= 0) {
                allPossibleStates.push_back(up);
            }
        }
        if (s->getStateIndexes().second > 0) {
            State<T>* left = this->m_matrixOfStates[s->getStateIndexes().first][s->getStateIndexes().second - 1];
            // check that the Left state cost >= to 0 and if it does add him to allPossibleStates - (i, j - 1) state
            if (left->getCost() >= 0) {
                allPossibleStates.push_back(left);
            }
        }
        return allPossibleStates;
    }

    /****************************************************************************************************
    * function name: getMatrix.
    * The Input: nothing.
    * The output: the matrix.
    * The Function operation: this function return the matrix.
    ****************************************************************************************************/
    vector<vector<string>> getMatrix() {
        return this->m_matrix;
    }

    /****************************************************************************************************
    * function name: ~NeighborsMatrix.
    * The Input: nothing.
    * The output: nothing.
    * The Function operation: the destructor make sure to erase all the things that were put on the
    *                         heap.
    ****************************************************************************************************/
    ~NeighborsMatrix() {
        for (auto &curRow : this->m_matrixOfStates) {
            for (auto &curState : curRow) {
                delete(curState);
            }
        }
    }
};


#endif
