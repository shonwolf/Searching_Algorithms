/***********************
* shon wolf
* 208581660
* 8921004
* project_part_2
**********************/
#ifndef BACKTRACESTATES_H
#define BACKTRACESTATES_H

#include <list>
#include "State.h"
using std::list;
template<class T> class BackTraceStates {
public:

    /****************************************************************************************************
    * function name: backTrace.
    * The Input: State<T>* s.
    * The output: list of the states from the initial state to the goal state.
    * The Function operation: this function return list of the states from the initial state to the
    *                         goal state.
    ****************************************************************************************************/
    list<State<T>*> backTrace(State<T>* s) {
        list<State<T>*> backTraceStates = {};
        // move on all the states by their parent and add them to the list by order - the initial will be in the front
        while (s != nullptr) {
            backTraceStates.push_front(s);
            s = s->getCameFrom();
        }
        return backTraceStates;
    }
};

#endif
