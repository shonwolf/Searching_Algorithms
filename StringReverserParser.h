/***********************
* shon wolf
* 208581660
* 8921004
* project_part_2
**********************/
#ifndef STRINGREVERSERPARSER_H
#define STRINGREVERSERPARSER_H

#include "Parser.h"
class StringReverserParser : public Parser<string, string> {
public:
    virtual string parseProblemToString(string s);
    virtual string parseSolutionToString(string s);
    virtual string parseStringToSolution(string solutionAsString, string matrixInString);
};

#endif
