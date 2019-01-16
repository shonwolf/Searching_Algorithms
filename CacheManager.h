/***********************
* shon wolf
* 208581660
* 8921004
* project_part_2
**********************/
#ifndef CACHEMANAGER_H
#define CACHEMANAGER_H

template<class Problem, class Solution> class CacheManager {
public:
    virtual bool doesHasSolutionToProblem(Problem p) = 0;
    virtual Solution getSolutionToProblem(Problem p) = 0;
    virtual void saveSolutionForProblem(Problem p, Solution s) = 0;
    virtual ~CacheManager() {}
};

#endif
