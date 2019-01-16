/***********************
* shon wolf
* 208581660
* 8921004
* project_part_2
**********************/
#ifndef ISEARCH_H
#define ISEARCH_H

#include "Searchable.h"
template<class T, class Solution> class ISearcher {
public:
    // the search method
    virtual Solution search(Searchable<T>* searchable) = 0;
    // get how many nodes were evaluated by the algorithm
    virtual int getNumberOfNodesEvaluated() = 0;
    virtual ~ISearcher() {}
};

#endif
