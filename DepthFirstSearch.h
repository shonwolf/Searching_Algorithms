/***********************
* shon wolf
* 208581660
* 8921004
* project_part_2
**********************/
#ifndef DEPTHFIRSTSEARCH_H
#define DEPTHFIRSTSEARCH_H

#include "ISearcher.h"
#include <stack>
#include <unordered_set>
#include "BackTraceStates.h"
using std::stack;
using std::unordered_set;
template<class T> class DepthFirstSearch : public ISearcher<T, list<State<T>*>>, public BackTraceStates<T> {
    // the members
    int m_evaluatedNodes;
public:

    /****************************************************************************************************
    * function name: this is constructor.
    * The Input: nothing.
    * The output: nothing.
    * The Function operation: initialize the members with the data.
    ****************************************************************************************************/
    DepthFirstSearch() {
        this->m_evaluatedNodes = 0;
    }

    /****************************************************************************************************
    * function name: search.
    * The Input: Searchable<T>* searchable.
    * The output: the shortest path from initial state to the goal state.
    * The Function operation: this function calculate the shortest path from initial state to the goal
    *                         state using best first search and return it.
    ****************************************************************************************************/
    virtual list<State<T>*> search(Searchable<T>* searchable) {

        /*
         * implementing Depth First Search from the link:
         * https://www.geeksforgeeks.org/iterative-depth-first-traversal/
         */
        stack<State<T>*> open = {};
        unordered_set<State<T>*> discovered = {};
        open.push(searchable->getInitialState());
        // start move on the graph
        while (!open.empty()) {
            State<T>* v = open.top();
            open.pop();
            this->m_evaluatedNodes++;
            // if the state is equal to the goal state, than backTrace throw the parents
            if (v->equals(searchable->getGoalState())) {
                return this->backTrace(v);
            }
            if (!discovered.count(v)) {
                discovered.insert(v);
            }
            list<State<T>*> successors = searchable->getAllPossibleStates(v);
            // move on the successors
            for (auto &w : successors) {
                if (!discovered.count(w)) {
                    w->setCameFrom(v);
                    open.push(w);
                }
            }
        }
        // empty list - there is no path
        return {};
    }

    /****************************************************************************************************
    * function name: getNumberOfNodesEvaluated.
    * The Input: nothing.
    * The output: the number of nodes were evaluated.
    * The Function operation: this function return the number of nodes were evaluated.
    ****************************************************************************************************/
    virtual int getNumberOfNodesEvaluated() {
        return this->m_evaluatedNodes;
    }
};

#endif
