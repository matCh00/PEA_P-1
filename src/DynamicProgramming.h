// algorytm programowania dynamicznego (algorytm Helda-Karpa)

#ifndef PEA_P_1_DYNAMICPROGRAMMING_H
#define PEA_P_1_DYNAMICPROGRAMMING_H

#include "Graph.h"

using namespace std;



class DynamicProgramming {

private:

    // liczba odwiedzonych miast
    int visitedCount;

    // długość minimalnej ścieżki -> [1][0] bo odwiedziliśmy 1 miasto (0) i zaczynamy od 0
    vector<vector<int>> cost;

    // minimalna ścieżka -> [1][0] bo odwiedziliśmy 1 miasto (0) i zaczynamy od 0
    vector<vector<vector<int>>> path;

    // część algorytmu - rekurencja
    int recursion(Graph *graph, int visitedCities, int currentPosition);


public:

    // konstruktor
    DynamicProgramming();

    // destruktor
    ~DynamicProgramming();

    // algorytm [argumenty 2 i 3 to sposób na zwrócenie więcej niż 1 parametru (zmiana parametrów poprzez referencję) ]
    void algorithmDynamicProgramming(Graph* graph, vector<int>& finalPath, int& finalCost);
};


#endif
