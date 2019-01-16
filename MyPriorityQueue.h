/***********************
* shon wolf
* 208581660
* 8921004
* project_part_2
**********************/
#ifndef MYPRIORITYQUEUE_H
#define MYPRIORITYQUEUE_H

#include "State.h"
#include <vector>
using std::vector;
template<class T> class MyPriorityQueue {
    // the members
    vector<State<T>*> m_priorityQueue;
public:

    /****************************************************************************************************
    * function name: this is constructor.
    * The Input: nothing.
    * The output: nothing.
    * The Function operation: initialize the members with the data.
    ****************************************************************************************************/
    MyPriorityQueue() {
        this->m_priorityQueue = {};
    }

    /****************************************************************************************************
    * function name: pool.
    * The Input: nothing.
    * The output: the element in the top of the queue and remove it.
    * The Function operation: this function return the element in the top of the queue and remove it.
    ****************************************************************************************************/
    State<T>* pool() {
        State<T>* temp = this->m_priorityQueue.front();
        this->m_priorityQueue.erase(this->m_priorityQueue.begin());
        return temp;
    }

    /****************************************************************************************************
    * function name: size.
    * The Input: nothing.
    * The output: the number of element in the queue.
    * The Function operation: this function return the number of element in the queue.
    ****************************************************************************************************/
    int size() {
        return this->m_priorityQueue.size();
    }

    /****************************************************************************************************
    * function name: contains.
    * The Input: State<T> state.
    * The output: true if the contain the state that gets, false otherwise.
    * The Function operation: this function return true if the contain the state that gets,
    *                         false otherwise.
    ****************************************************************************************************/
    bool contains(State<T>* state) {

        /*
         * check if there is state in the queue's copy who equals to the one we get, and if there is than the queue
         * contains him.
         */
        for (auto &curState : this->m_priorityQueue) {
            if (curState->equals(state)) {
                return true;
            }
        }
        return false;
    }

    /****************************************************************************************************
    * function name: add.
    * The Input: State<T> state.
    * The output: nothing.
    * The Function operation: this function adds state to the priority queue.
    ****************************************************************************************************/
    void add(State<T>* state) {
        if (!this->m_priorityQueue.empty()) {
            vector<State<T>*> sortedVectorWithNewState = {};
            bool gotIn = false;
            // keep the list sorted because every time add State to it add him to the place he should be in
            for (auto &curState : this->m_priorityQueue) {
                if (!gotIn && state->getCostUntilMe() < curState->getCostUntilMe()) {
                    sortedVectorWithNewState.push_back(state);
                    gotIn = true;
                }
                sortedVectorWithNewState.push_back(curState);
            }
            if (!gotIn) {
                sortedVectorWithNewState.push_back(state);
            }
            this->m_priorityQueue = sortedVectorWithNewState;
        } else {
            this->m_priorityQueue.push_back(state);
        }
    }

    /****************************************************************************************************
    * function name: remove.
    * The Input: State<T> state.
    * The output: nothing.
    * The Function operation: this function removes state from the priority queue.
    ****************************************************************************************************/
    void remove(State<T>* state) {
        vector<State<T>*> newPriorityQueue = {};
        for (auto &curState : this->m_priorityQueue) {
            if (curState->equals(state)) {
                continue;
            }
            newPriorityQueue.push_back(curState);
        }
        this->m_priorityQueue = newPriorityQueue;
    }
};

#endif
