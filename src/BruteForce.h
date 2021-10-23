// algorytm przeglądu zupełnego

#ifndef PEA_P_1_BRUTEFORCE_H
#define PEA_P_1_BRUTEFORCE_H

#include "Graph.h"

using namespace std;


// klasa reprezentująca algorytm BF
class BruteForce {

private:

    // minimalna ścieżka
    vector<int> path;

    // długość minimalnej ścieżki
    int cost;


public:

    // konstruktor
    BruteForce();

    // destruktor
    ~BruteForce();

    // algorytm [argumenty 3 i 4 to sposób na zwrócenie więcej niż 1 parametru (zmiana parametrów poprzez referencję) ]
    void algorithmBruteForce(Graph graph, int source, vector<int>& finalPath, int& finalCost);
};


#endif
