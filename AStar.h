/***********************
* shon wolf
* 208581660
* 8921004
* project_part_2
**********************/
#ifndef ASTAR_H
#define ASTAR_H

#include "ISearcher.h"
#include <unordered_set>
#include <unordered_map>
#include <math.h>
#include "BackTraceStates.h"
#include "State.h"
#include <vector>
using namespace std;
template<class T> class AStar : public ISearcher<T, list<State<T>*>>, public BackTraceStates<T> {
    // the members
    int m_evaluatedNodes;

    /****************************************************************************************************
    * function name: heuristic.
    * The Input: State<T>* node, State<T>* goalNode.
    * The output: the distance between the node to the goalNode.
    * The Function operation: this function calculate the distance from the node to the goalNode using
    *                         equation: distance = root((x1 - x2)^2 + (y1 - y2)^2).
    ****************************************************************************************************/
    double heuristic(State<T>* node, State<T>* goalNode) {
        double x1 = node->getStateIndexes().first;
        double x2 = goalNode->getStateIndexes().first;
        double y1 = node->getStateIndexes().second;
        double y2 = goalNode->getStateIndexes().second;
        // distance = root((x1 - x2)^2 + (y1 - y2)^2) ~ |x1 - x2| + |y1 - y2|
        double distance = abs(x1 - x2) + abs(y1 - y2);
        return distance;
    }

    /****************************************************************************************************
    * function name: insertInOrderedPosition.
    * The Input: vector<State<T>*> open, State<T>* state.
    * The output: the vector with the state ordered inside him.
    * The Function operation: this function insert the state to the right position in the vector and
    *                         return it.
    ****************************************************************************************************/
    vector<State<T>*> insertInOrderedPosition(vector<State<T>*> open, State<T>* state) {
        vector<State<T>*> newVector;
        if (!open.empty()) {
            // insert the state in the right position
            while (open.size() > 0) {
                State<T>* s = open.front();
                if (s->getHeuristic() < state->getHeuristic()) {
                    newVector.push_back(s);
                    open.erase(open.begin());
                } else {
                    break;
                }
            }
            // push to the right position
            newVector.push_back(state);
            // put in the vector all the rest of the States
            for (auto &curState : open) {
                newVector.push_back(curState);
            }
        } else {
            newVector.push_back(state);
        }
        return newVector;
    }
public :

    /****************************************************************************************************
    * function name: this is constructor.
    * The Input: nothing.
    * The output: nothing.
    * The Function operation: initialize the members with the data.
    ****************************************************************************************************/
    AStar() {
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
        vector<State<T>*> open = {};
        unordered_set<State<T>*> closed = {};
        searchable->getInitialState()->setCostUntilMe(searchable->getInitialState()->getCost());
        // initial heuristic for order with it the States
        searchable->getInitialState()->setHeuristic(this->heuristic(searchable->getInitialState(),
                                                                    searchable->getGoalState()));
        open.push_back(searchable->getInitialState());
        closed.insert(searchable->getInitialState());
        // move on the graph
        while(!open.empty()){
            State<T>* n = open.front();
            closed.insert(n);
            open.erase(open.begin());
            this->m_evaluatedNodes++;
            // if we got to the goalState
            if(n->equals(searchable->getGoalState())){
                return this->backTrace(n);
            }
            list<State<T>*> successors = searchable->getAllPossibleStates(n);
            // move on all the successors
            for(auto &s : successors) {
                if(!closed.count(s)) {
                    if (s->getCostUntilMe() > s->getCost() + n->getCostUntilMe() || s->getCostUntilMe() == 0) {
                        s->setCameFrom(n);
                        s->setCostUntilMe(s->getCost() + n->getCostUntilMe());
                        s->setHeuristic(s->getCostUntilMe() + this->heuristic(s, searchable->getGoalState()));
                    }
                    closed.insert(s);
                    open = this->insertInOrderedPosition(open, s);
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
