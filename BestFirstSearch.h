/***********************
* shon wolf
* 208581660
* 8921004
* project_part_2
**********************/
#ifndef BESTFIRSTSEARCH_H
#define BESTFIRSTSEARCH_H

#include "Searcher.h"
#include <unordered_set>
#include "BackTraceStates.h"
using std::unordered_set;
template<class T> class BestFirstSearch : public Searcher<T, list<State<T>*>>, public BackTraceStates<T> {
public:

    /****************************************************************************************************
    * function name: search.
    * The Input: Searchable<T>* searchable.
    * The output: the shortest path from initial state to the goal state.
    * The Function operation: this function calculate the shortest path from initial state to the goal
    *                         state using best first search and return it.
    ****************************************************************************************************/
    virtual list<State<T>*> search(Searchable<T>* searchable) {

        /*
         * implementing Best First Search from the link:
         * https://ipfs.io/ipfs/QmXoypizjW3WknFiJnKLwHCnL72vedxjQkDDP1mXWo6uco/wiki/Best-first_search.html
         */
        this->addToOpenList(searchable->getInitialState());
        // a set of states already evaluated
        unordered_set<State<T>*> closed = {};
        while (this->openListSize() > 0) {
            State<T>* n = this->popOpenList();
            closed.insert(n);
            // if the state is equal to the goal state, than backTrace throw the parents
            if (n->equals(searchable->getGoalState())) {
                return this->backTrace(n);
            }
            list<State<T>*> successors = searchable->getAllPossibleStates(n);
            // move on all the successors
            for (auto &s : successors) {
                if (!closed.count(s) && !this->openListContains(s)) {
                    s->setCameFrom(n);
                    s->setCostUntilMe(s->getCost() + n->getCostUntilMe());
                    this->addToOpenList(s);
                } else if (!closed.count(s)) {
                    if (s->getCameFrom()->getCostUntilMe() > n->getCostUntilMe()) {
                        s->setCameFrom(n);
                        s->setCostUntilMe(s->getCost() + n->getCostUntilMe());
                        // make sure the priority queue keep be ordered
                        this->removeFromOpenList(s);
                        this->addToOpenList(s);
                    }
                }
            }
        }
        // empty list - there is no path
        return {};
    }
};

#endif
