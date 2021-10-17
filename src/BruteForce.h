// algorytm przeglądu zupełnego

#pragma once
#include "Graph.h"
#include <algorithm>

using namespace std;



class BruteForce : public Graph {

private:

    // pełna ścieżka
    vector<int> path;

    // minimalna pojedyncza ścieżka
    int countMinPath;


public:

    // konstruktor
    BruteForce();

    // destruktor
    ~BruteForce();

    // algorytm
    int algorithmBruteForce(int source);
};
