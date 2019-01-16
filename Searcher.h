/***********************
* shon wolf
* 208581660
* 8921004
* project_part_2
**********************/
#ifndef SEARCHER_H
#define SEARCHER_H

#include "ISearcher.h"
#include "MyPriorityQueue.h"
#include "State.h"
template<class T, class Solution> class Searcher : public ISearcher<T, Solution> {
    // the members
    MyPriorityQueue<T> m_openList;
    int m_evaluatedNodes;
public:

    /****************************************************************************************************
    * function name: this is constructor.
    * The Input: nothing.
    * The output: nothing.
    * The Function operation: initialize the members with the data.
    ****************************************************************************************************/
    Searcher() {
        this->m_openList = MyPriorityQueue<T>();
        this->m_evaluatedNodes = 0;
    }

    // the search method
    virtual Solution search(Searchable<T>* searchable) = 0;

    /****************************************************************************************************
    * function name: getNumberOfNodesEvaluated.
    * The Input: nothing.
    * The output: the number of nodes were evaluated.
    * The Function operation: this function return the number of nodes were evaluated.
    ****************************************************************************************************/
    virtual int getNumberOfNodesEvaluated() {
        return this->m_evaluatedNodes;
    }

    /****************************************************************************************************
    * function name: popOpenList.
    * The Input: nothing.
    * The output: the top state in the priority queue.
    * The Function operation: this function add one to the evaluatedNodes counter and return the top
    *                         state in the priority queue (and remove him).
    ****************************************************************************************************/
    virtual State<T>* popOpenList() {
        this->m_evaluatedNodes++;
        return this->m_openList.pool();
    }

    /****************************************************************************************************
    * function name: openListSize.
    * The Input: nothing.
    * The output: the size of the priority queue.
    * The Function operation: this function return the size of the priority queue.
    ****************************************************************************************************/
    virtual int openListSize() {
        return this->m_openList.size();
    }

    /****************************************************************************************************
    * function name: addToOpenList.
    * The Input: State<T> state.
    * The output: nothing.
    * The Function operation: this function add state to the priority queue.
    ****************************************************************************************************/
    virtual void addToOpenList(State<T>* state) {
        this->m_openList.add(state);
    }

    /****************************************************************************************************
    * function name: removeFromOpenList.
    * The Input: State<T> state.
    * The output: nothing.
    * The Function operation: this function removes state from the priority queue.
    ****************************************************************************************************/
    virtual void removeFromOpenList(State<T>* state) {
        this->m_openList.remove(state);
    }

    /****************************************************************************************************
    * function name: openListContains.
    * The Input: State<T> state.
    * The output: true if the priority queue contains the state, false otherwise.
    * The Function operation: this function return true if the priority queue contains the state,
    *                         false otherwise.
    ****************************************************************************************************/
    virtual bool openListContains(State<T>* state) {
        if (this->m_openList.contains(state)) {
            return true;
        }
        return false;
    }

    virtual ~Searcher() {}
};

#endif
