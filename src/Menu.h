// menu projektu

#ifndef PEA_P_1_MENU_H
#define PEA_P_1_MENU_H

#include "BranchAndBound.h"
#include "BruteForce.h"
#include "DynamicProgramming.h"
#include "Graph.h"

using namespace std;



class Menu {

private:

    // graf
    Graph* graph;

    // algorytm BF
    BruteForce* bruteForce;

    // algorytm BB
    BranchAndBound* branchAndBound;

    // algorytm DP
    DynamicProgramming* dynamicProgramming;


public:

    // konstruktor
    Menu();

    // destruktor
    ~Menu();

    // start
    void startMenu();
};


#endif

