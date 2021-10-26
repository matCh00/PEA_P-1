// algorytm przeglądu zupełnego

#ifndef PEA_P_1_BRUTEFORCE_H
#define PEA_P_1_BRUTEFORCE_H

#include "../_structures/Graph.h"

using namespace std;


// klasa reprezentująca algorytm BF
class BruteForce {

private:

    // minimalna ścieżka
    vector<int> path;

    // długość minimalnej ścieżki
    int cost;

    // część algorytmu - policzenie pojedynczej ścieżki
    static int findPath(Graph* graph, vector<int> cities, int size);


public:

    // konstruktor
    BruteForce();

    // destruktor
    ~BruteForce();

    // algorytm - permutacje
    // [argumenty 2 i 3 to sposób na zwrócenie więcej niż 1 parametru (zmiana parametrów poprzez referencję) ]
    void algorithmBruteForce(Graph* graph, vector<int>& finalPath, int& finalCost);
};


#endif
