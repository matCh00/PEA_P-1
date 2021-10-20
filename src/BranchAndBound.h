// algorytm podziału i ograniczeń

#pragma once
#include "Graph.h"

using namespace std;


// klasa pomocnicza do algorytmu przechowująca wyniki redukcji
class BB {

    // aktualnie odwiedzone miasto
    int currentCity;

    // koszt przejścia do danego miasta po wcześniejszej ścieżce
    int reduction;

    // tablica odwiedzonych miast
    bool* visited;

    // ścieżka
    vector<int> path;
};



// klasa reprezentująca algorytm BB
class BranchAndBound {

private:

    // minimalna ścieżka
    vector<int> pathOfCities;

    // długość minimalnej ścieżki
    int pathValue;


public:

    // konstruktor
    BranchAndBound();

    // destruktor
    ~BranchAndBound();

    // algorytm [argumenty 3 i 4 to sposób na zwrócenie więcej niż 1 parametru (zmiana parametrów poprzez referencję) ]
    void algorithmBranchAndBound(Graph graph, int source, vector<int>& finalPath, int& finalPathValue);

    // redukcja grafu
    int reduceGraph(int** distances);

    // zaznaczenie kroku
    int** markStep(int row, int col, int** distances);
};

