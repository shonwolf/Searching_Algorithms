/***********************
* shon wolf
* 208581660
* 8921004
* project_part_2
**********************/
#include "StringReverser.h"

/****************************************************************************************************
* function name: solve.
* The Input: Problem p the problem, in this case a string.
* The output: the Solution, in this case the reverse string.
* The Function operation: this function calculate the reverse string and return it.
****************************************************************************************************/
string StringReverser::solve(string p) {
    reverse(p.begin(), p.end());
    return p;
}
