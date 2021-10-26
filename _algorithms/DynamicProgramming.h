// algorytm programowania dynamicznego (algorytm Helda-Karpa)

#ifndef PEA_P_1_DYNAMICPROGRAMMING_H
#define PEA_P_1_DYNAMICPROGRAMMING_H

#include "../_structures/Graph.h"

using namespace std;


class DynamicProgramming {

private:

    // minimalna ścieżka
    vector<int> path;

    // długość minimalnej ścieżki
    int cost;

    // część algorytmu - rekurencja
    int findPath(Graph *graph, int visitedCities, int currentPosition);

    int shift;
    vector<vector<int>> rememberPath;
    vector<vector<int>> rememberDistance;


public:

    // konstruktor
    DynamicProgramming();

    // destruktor
    ~DynamicProgramming();

    // algorytm [argumenty 2 i 3 to sposób na zwrócenie więcej niż 1 parametru (zmiana parametrów poprzez referencję) ]
    void algorithmDynamicProgramming(Graph* graph, vector<int>& finalPath, int& finalCost);
};


#endif
