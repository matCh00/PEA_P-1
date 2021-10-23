// algorytm programowania dynamicznego (algorytm Helda-Karpa)

#pragma once
#include "Graph.h"

using namespace std;



class DynamicProgramming {

private:

    // minimalna ścieżka
    vector<int> path;

    // długość minimalnej ścieżki
    int cost;

    vector<vector<int>> rememberPath;
    vector<vector<int>> rememberDistance;


public:

    // konstruktor
    DynamicProgramming();

    // destruktor
    ~DynamicProgramming();

    // algorytm [argumenty 3 i 4 to sposób na zwrócenie więcej niż 1 parametru (zmiana parametrów poprzez referencję) ]
    void algorithmDynamicProgramming(Graph graph, int source, vector<int>& finalPath, int& finalCost);

    int findMinTourCost(Graph graph, int currentVertex, int position);
};
