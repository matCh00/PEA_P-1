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
    vector<vector<int>> currentGraph;

    // koszt do danego wierzchołka po wcześniejszej ścieżce
    int temporaryCost;

    // odwiedzone wierzchołki
    vector<bool> visited;

    // aktualna ścieżka
    vector<int> path;
};



// klasa reprezentująca algorytm BB
class BranchAndBound{

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

    BB matrixStartReduction(vector<vector<int>> graph, int verticles, int source);
    vector<vector<int>> copyGraph(vector<vector<int>> graph, int size);
    vector<bool> copyVisited(vector<bool> visited, int size);
    BB reducing(Graph graph, BB given, int source, int endVert, int firstVertex);
    bool isVisitedLeft(vector<bool> visited, int size);
};

