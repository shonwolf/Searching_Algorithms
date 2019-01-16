/***********************
* shon wolf
* 208581660
* 8921004
* project_part_2
**********************/
#ifndef SEARCHABLE_H
#define SEARCHABLE_H

#include <list>
#include "State.h"
using std::list;
template<class T> class Searchable {
public:
    virtual State<T>* getInitialState() = 0;
    virtual State<T>* getGoalState() = 0;
    // this function also does setCameFrom(s) for all the successors she puts in the list she she returns
    virtual list<State<T>*> getAllPossibleStates(State<T>* s) = 0;
    virtual ~Searchable() {}
};

#endif
