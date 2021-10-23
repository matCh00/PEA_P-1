// menu projektu

#pragma once
#include "BranchAndBound.h"
#include "BruteForce.h"
#include "DynamicProgramming.h"
#include "Graph.h"

using namespace std;



class Menu {

private:

    // graf
    Graph graph;

    // algorytm BF
    BruteForce bruteForce;

    // algorytm BB
    BranchAndBound branchAndBound;

    // algorytm DP
    DynamicProgramming dynamicProgramming;


public:

    // konstruktor
    Menu();

    // destruktor
    ~Menu();

    // start
    void startMenu();
};

