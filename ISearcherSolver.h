/***********************
* shon wolf
* 208581660
* 8921004
* project_part_2
**********************/
#ifndef ISEARCHERSOLVER_H
#define ISEARCHERSOLVER_H

#include "Solver.h"
#include "Searchable.h"
#include "ISearcher.h"
template<class T, class Problem, class Solution>class ISearcherSolver : public Solver<Searchable<T>*, Solution> {
    // the members
    ISearcher<T, Solution>* m_iSearcher;
public:

    /****************************************************************************************************
    * function name: this is constructor.
    * The Input: nothing.
    * The output: nothing.
    * The Function operation: initialize the members with the data.
    ****************************************************************************************************/
    ISearcherSolver(ISearcher<T, Solution>* iSearcher) {
        this->m_iSearcher = iSearcher;
    }

    /****************************************************************************************************
    * function name: solve.
    * The Input: Problem p the problem, in this case a Searchable<T>.
    * The output: the Solution, in this case the reverse string.
    * The Function operation: this function calculate the reverse string and return it.
    ****************************************************************************************************/
    virtual Solution solve(Searchable<T>* p) {
        return this->m_iSearcher->search(p);
    }
    virtual ~ISearcherSolver() {}
};

#endif
