// algorytm podziału i ograniczeń

#ifndef PEA_P_1_BRANCHANDBOUND_H
#define PEA_P_1_BRANCHANDBOUND_H

#include "../_structures/Graph.h"

using namespace std;


// klasa reprezentująca algorytm BB
class BranchAndBound{

private:

    // minimalna ścieżka
    vector<int> path;

    // długość minimalnej ścieżki
    int cost;

    // część algorytmu
    void findPath(Graph *graph, int currBound, int currWeight, int level, vector<int> currPath);

    // tablica odwiedzonych miast
    vector<bool> visited;

    // robocza tablica - aktualna ścieżka
    vector<int> currPath;

    // szukanie pierwszej minimalnej ścieżki kończącej się na i
    int firstMin(Graph *graph, int i);

    // szukanie drugiej minimalnej ścieżki kończącej się na i
    int secondMin(Graph *graph, int i);



public:

    // konstruktor
    BranchAndBound();

    // destruktor
    ~BranchAndBound();

    // algorytm [argumenty 2 i 3 to sposób na zwrócenie więcej niż 1 parametru (zmiana parametrów poprzez referencję) ]
    void algorithmBranchAndBound(Graph* graph, vector<int>& finalPath, int& finalPathValue);
};


#endif

