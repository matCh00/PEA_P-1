// algorytm przeglądu zupełnego

#pragma once
#include "Graph.h"
#include <algorithm>

using namespace std;


// klasa reprezentująca algorytm BF
class BruteForce {

private:

    // minimalna ścieżka
    vector<int> pathOfCities;

    // długość minimalnej ścieżki
    int pathValue;


public:

    // konstruktor
    BruteForce();

    // destruktor
    ~BruteForce();

    // algorytm [argumenty 3 i 4 to sposób na zwrócenie więcej niż 1 parametru (zmiana parametrów poprzez referencję) ]
    void algorithmBruteForce(Graph graph, int source, vector<int>& finalPath, int& finalPathValue);
};
