/***********************
* shon wolf
* 208581660
* 8921004
* project_part_2
**********************/
#ifndef SOLVER_H
#define SOLVER_H

#include <string>
template<class Problem, class Solution> class Solver {
public:
    virtual Solution solve(Problem p) = 0;
    virtual ~Solver() {}
};

#endif
