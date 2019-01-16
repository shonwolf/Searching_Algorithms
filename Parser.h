/***********************
* shon wolf
* 208581660
* 8921004
* project_part_2
**********************/
#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "vector"
using namespace std;
template<class Problem, class Solution> class Parser {
public:
    virtual string parseProblemToString(Problem p) = 0;
    virtual string parseSolutionToString(Solution s) = 0;
    virtual Solution parseStringToSolution(string solutionAsString, string matrixInString) = 0;
    virtual ~Parser() {}
};

#endif
