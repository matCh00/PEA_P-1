/*
 *  algorytm podziału i ograniczeń
 */

#ifndef PEA_P_1_BRANCHANDBOUND_H
#define PEA_P_1_BRANCHANDBOUND_H

#include "../_structures/Graph.h"

using namespace std;


class BranchAndBound {

private:

    //
    int bestResult;

    //
    int numberOfCities;

    //
    int* solution;

    //
    int* cities;

    //
    int* possibleSolution;

    //
    bool* visited;

    //
    vector<vector<int>> matrixOfDistance;

    // część algorytmu
    void toSolution();

    // część algorytmu
    int minLine(int);

    // część algorytmu
    void treeSearch(int, int, int);


public:

    // konstruktor
    BranchAndBound();

    // destruktor
    ~BranchAndBound();

    // algorytm
    int algorithmBranchAndBound(vector<vector<int>> matrix, int *bestPath);
};


#endif

