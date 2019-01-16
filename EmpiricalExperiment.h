/***********************
* shon wolf
* 208581660
* 8921004
* project_part_2
**********************/
#ifndef EMPIRICALEXPERIMENT_H
#define EMPIRICALEXPERIMENT_H

#include <string>
#include <fstream>
#include "BestFirstSearch.h"
#include "DepthFirstSearch.h"
#include "BreadthFirstSearch.h"
#include "AStar.h"
#include "NeighborsMatrix.h"
#include <vector>
using std::string;
using std::fstream;
using std::__throw_runtime_error;
using std::vector;
class EmpiricalExperiment {
    void eraseSpaces(string& val);
public:
    void doExperiment();
};

#endif
