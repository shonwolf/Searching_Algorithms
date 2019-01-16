/***********************
* shon wolf
* 208581660
* 8921004
* project_part_2
**********************/
#ifndef BREADTHFIRSTSEARCH_H
#define BREADTHFIRSTSEARCH_H

#include "ISearcher.h"
#include <queue>
#include <unordered_set>
#include "BackTraceStates.h"
using std::queue;
using std::unordered_set;
template<class T> class BreadthFirstSearch : public ISearcher<T, list<State<T>*>>, public BackTraceStates<T> {
    // the members
    int m_evaluatedNodes;
public:

    /****************************************************************************************************
    * function name: this is constructor.
    * The Input: nothing.
    * The output: nothing.
    * The Function operation: initialize the members with the data.
    ****************************************************************************************************/
    BreadthFirstSearch() {
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
        /* implementing Breadth First Search from the link: wikipedia in Hebrew with changes */
        queue<State<T>*> open = {};
        unordered_set<State<T>*> visited = {};
        unordered_set<State<T>*> close = {};
        open.push(searchable->getInitialState());
        visited.insert(searchable->getInitialState());
        // start move on the graph
        while (!open.empty()) {
            State<T>* node = open.front();
            open.pop();
            this->m_evaluatedNodes++;
            visited.erase(node);
            close.insert(node);
            // if we arrived to the goal state we can restore the path throw the parents
            if (node->equals(searchable->getGoalState())) {
                return this->backTrace(node);
            }
            list<State<T>*> successors = searchable->getAllPossibleStates(node);
            // move on the successors
            for (auto &child : successors) {
                if (!close.count(child) && !visited.count(child)) {
                    open.push(child);
                    child->setCameFrom(node);
                    visited.insert(child);
                } else if (visited.count(child)) {
                    child->setCameFrom(node);
                    close.insert(child);
                    visited.erase(child);
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
