/***********************
* shon wolf
* 208581660
* 8921004
* project_part_2
**********************/
#ifndef STATE_H
#define STATE_H

#include <string>
using std::string;
using std::pair;

template<class T> class State {
    // the members
    // the state representation
    T m_state;
    // cost to reach this state
    double m_cost;
    // the state we came from to this state
    State<T>* m_cameFrom;
    pair<int, int> m_stateIndexes;
    double m_costUntilMe;
    double m_heuristic;
public:

    /****************************************************************************************************
    * function name: this is constructor.
    * The Input: nothing.
    * The output: nothing.
    * The Function operation: initialize the members with the data.
    ****************************************************************************************************/
    State() {
        /* default initializations */
        this->m_state = "default";
        this->m_cost = 0;
        this->m_cameFrom = nullptr;
        this->m_stateIndexes = pair<int, int>(-1, -1);
        this->m_costUntilMe = 0;
        this->m_heuristic = 0;
    }

    /****************************************************************************************************
    * function name: this is constructor.
    * The Input: T state, double cost, pair<int, int> stateIndexes.
    * The output: nothing.
    * The Function operation: initialize the members with the data.
    ****************************************************************************************************/
    State(T state, double cost, pair<int, int> stateIndexes) {
        this->m_state = state;
        this->m_cost = cost;
        // at start initialize to nullptr that for every state who do not has state he came from we will know it
        this->m_cameFrom = nullptr;
        this->m_stateIndexes = stateIndexes;
        this->m_costUntilMe = 0;
        this->m_heuristic = 0;
    }

    /****************************************************************************************************
    * function name: this is constructor.
    * The Input: T state, double cost, State<T>* cameFrom, pair<int, int> stateIndexes.
    * The output: nothing.
    * The Function operation: initialize the members with the data.
    ****************************************************************************************************/
    State(T state, double cost, State<T>* cameFrom, pair<int, int> stateIndexes) {
        this->m_state = state;
        this->m_cost = cost;
        this->m_cameFrom = cameFrom;
        this->m_stateIndexes = stateIndexes;
        this->m_costUntilMe = 0;
        this->m_heuristic = 0;
    }
    double getHeuristic() {
        return this->m_heuristic;
    }
    void setHeuristic(double heuristic) {
        this->m_heuristic = heuristic;
    }

    /****************************************************************************************************
    * function name: equals.
    * The Input: State<T> s.
    * The output: true if this state and the state that the function gets are equals, false otherwise.
    * The Function operation: this function checks if the states are equals and return true if they do,
    *                         false otherwise.
    ****************************************************************************************************/
    bool equals(State<T>* s) const {
        return (this->m_state == s->m_state);
    }

    /****************************************************************************************************
    * function name: getCost.
    * The Input: nothing.
    * The output: the state.
    * The Function operation: this function return the state.
    ****************************************************************************************************/
    T getState() const {
        return this->m_state;
    }

    /****************************************************************************************************
    * function name: setCost.
    * The Input: double cost.
    * The output: nothing.
    * The Function operation: this function set the cost of this state.
    ****************************************************************************************************/
    void setCost(double cost) {
        this->m_cost = cost;
    }

    /****************************************************************************************************
    * function name: getCost.
    * The Input: nothing.
    * The output: the cost of this state.
    * The Function operation: this function return the cost of this state.
    ****************************************************************************************************/
    double getCost() const {
        return this->m_cost;
    }

    /****************************************************************************************************
    * function name: setCameFrom.
    * The Input: State<T> cameFrom.
    * The output: nothing.
    * The Function operation: this function set the state cameFrom of this state.
    ****************************************************************************************************/
    void setCameFrom(State<T>* cameFrom) {
        this->m_cameFrom = cameFrom;
    }

    /****************************************************************************************************
    * function name: getCameFrom.
    * The Input: nothing.
    * The output: the cameFrom state of this state.
    * The Function operation: this function return the cameFrom state of this state.
    ****************************************************************************************************/
    State<T>* getCameFrom() const {
        return this->m_cameFrom;
    }

    /****************************************************************************************************
    * function name: getStateIndexes.
    * The Input: nothing.
    * The output: the state indexes.
    * The Function operation: this function return the state indexes.
    ****************************************************************************************************/
    pair<int, int> getStateIndexes() const {
        return this->m_stateIndexes;
    }

    /****************************************************************************************************
    * function name: getCostUntilMe.
    * The Input: nothing.
    * The output: the state indexes.
    * The Function operation: this function return the cost until this state.
    ****************************************************************************************************/
    double getCostUntilMe() {
        return this->m_costUntilMe;
    }

    /****************************************************************************************************
    * function name: setCostUntilMe.
    * The Input: double costUntilMe.
    * The output: nothing.
    * The Function operation: this function set the cost until this state.
    ****************************************************************************************************/
    void setCostUntilMe(double costUntilMe) {
        this->m_costUntilMe = costUntilMe;
    }

    /****************************************************************************************************
    * function name: operator<.
    * The Input: const State& other.
    * The output: true if this is smaller than the other, false otherwise.
    * The Function operation: this function return true if this is smaller than the other, false
    *                         otherwise.
    ****************************************************************************************************/
    bool operator<(const State& other) const {
        if(this->m_cost < other.m_cost) {
            return true;
        }
        return false;
    }

    /****************************************************************************************************
    * function name: operator==.
    * The Input: const State& other.
    * The output: true if this is smaller than the other, false otherwise.
    * The Function operation: this function return true if this is smaller than the other, false
    *                         otherwise.
    ****************************************************************************************************/
    bool operator==(const State& other) const {
        return (this->m_state == other.m_state);
    }
};

#endif
