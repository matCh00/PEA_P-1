// algorytm podziału i ograniczeń

#ifndef PEA_P_1_BRANCHANDBOUND_H
#define PEA_P_1_BRANCHANDBOUND_H

#include "../_structures/Graph.h"

using namespace std;


// klasa reprezentująca algorytm BB
class BranchAndBound {

public:

    int* solution;
    int bestResult;
    int numberOfCities;
    vector<vector<int>> matrixOfDistance;

    int* cities;
    int* possibleSolution;
    bool* visited;

    void toSolution();
    int minLine(int);
    void treeSearch(int, int, int);

public:

    int algorithmBranchAndBound(vector<vector<int>> matrix, int *bestPath);
    void clear();

    // konstruktor
    BranchAndBound();
    // destruktor
    ~BranchAndBound();

};



#endif

