/***********************
* shon wolf
* 208581660
* 8921004
* project_part_2
**********************/
#include "MyParallelServer.h"
#include "AStar.h"
#include "ISearcherSolver.h"
#include "NeighborsMatrixParser.h"
#include "FileCacheManager.h"
#include "MyClientHandler.h"
using std::string;
/*****************************************************************************************************
* function name: main.
* The Input: int argc, char* argv[].
* The output: number who show the exit of the process.
* The Function operation: this function start all the program.
****************************************************************************************************/
int main(int argc, char* argv[]) {
    // get the port to connect throw from the command line
    int port = stoi(argv[1]);
    MyParallelServer mss = MyParallelServer();
    AStar<string>* aStar = new AStar<string>();
    ISearcherSolver<string, Searchable<string>*, list<State<string>*>>* is;
    is = new ISearcherSolver<string, Searchable<string>*, list<State<string>*>>(aStar);
    NeighborsMatrixParser<string>* nmp = new NeighborsMatrixParser<string>();
    FileCacheManager<Searchable<string>*, list<State<string>*>>* fcm;
    fcm = new FileCacheManager<Searchable<string>*, list<State<string>*>>(nmp, "fileCacheManagerMatrix.txt");
    MyClientHandler<Searchable<string>*, list<State<string>*>>* mch;
    mch = new MyClientHandler<Searchable<string>*, list<State<string>*>>(is, fcm, nmp);
    mss.open(port, mch);
    delete(aStar);
    delete(is);
    delete(fcm);
    delete(nmp);
    delete(mch);
    return 0;
}