// algorytm programowania dynamicznego (algorytm Helda-Karpa)

#ifndef PEA_P_1_DYNAMICPROGRAMMING_H
#define PEA_P_1_DYNAMICPROGRAMMING_H

#include "Graph.h"

using namespace std;



class DynamicProgramming {

private:

    // minimalna ścieżka
    vector<int> path;

    // długość minimalnej ścieżki
    int cost;

    // część algorytmu - rekurencja
    int recursionTSP(Graph *graph, int visitedCities, int currentPos);


    int visitedAll;
    vector<vector<int>> savedPaths;
    vector<vector<string>> shortestPath;


public:

    // konstruktor
    DynamicProgramming();

    // destruktor
    ~DynamicProgramming();

    // algorytm [argumenty 2 i 3 to sposób na zwrócenie więcej niż 1 parametru (zmiana parametrów poprzez referencję) ]
    void algorithmDynamicProgramming(Graph* graph, vector<int>& finalPath, int& finalCost);
};


#endif
