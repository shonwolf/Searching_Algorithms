/***********************
* shon wolf
* 208581660
* 8921004
* project_part_2
**********************/
#ifndef STRINGREVERSER_H
#define STRINGREVERSER_H

#include "Solver.h"
#include <string>
#include <bits/stdc++.h>
using std::string;
class StringReverser : public Solver<string, string> {
public:
    virtual string solve(string p);
    virtual ~StringReverser() {}
};

#endif
