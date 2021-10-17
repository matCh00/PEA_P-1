// algorytm przeglądu zupełnego

#pragma once
#include "Graph.h"
#include <algorithm>

using namespace std;



class BruteForce {

private:

    // pełna ścieżka
    vector<int> path;

    // minimalna ścieżka (wartość)
    int valueOfMinPath;


public:

    // konstruktor
    BruteForce();

    // destruktor
    ~BruteForce();

    // algorytm
    int algorithmBruteForce(Graph graph, int source);
};
