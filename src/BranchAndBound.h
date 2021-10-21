// algorytm podziału i ograniczeń

#pragma once
#include "Graph.h"

using namespace std;


// klasa pomocnicza do algorytmu przechowująca wyniki redukcji
class BB {

public:

    // aktualnie sprawdzany wierzchołek
    int currentVertex;

    // aktualnie przechowywany graf
    int **currentGraph;

    // koszt do danego wierzchołka po wcześniejszej ścieżce
    int temporaryCost;

    // odwiedzone wierzchołki
    bool* visited;

    // aktualna ścieżka
    vector<int> path;
};



// klasa reprezentująca algorytm BB
class BranchAndBound {

private:

    // minimalna ścieżka
    vector<int> path;

    // długość minimalnej ścieżki
    int cost;


public:

    // konstruktor
    BranchAndBound();

    // destruktor
    ~BranchAndBound();

    // algorytm [argumenty 3 i 4 to sposób na zwrócenie więcej niż 1 parametru (zmiana parametrów poprzez referencję) ]
    void algorithmBranchAndBound(Graph graph, int source, vector<int>& finalPath, int& finalPathValue);

    BB matrixStartReduction(int** graph, int verticles, int source);
    int** copyGraph(int**graph, int size);
    bool* copyVisited(bool*visited, int size);
    BB reducing(Graph graph, BB given, int source, int endVert, int firstVertex);
    bool isVisitedLeft(bool* visited, int size);
};

