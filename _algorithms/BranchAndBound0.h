#ifndef PEA_P_1_BRANCHANDBOUND0_H
#define PEA_P_1_BRANCHANDBOUND0_H

#include "../_structures/Graph.h"

using namespace std;


// klasa pomocnicza do algorytmu przechowująca wyniki redukcji
class BB0 {

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
class BranchAndBound0{

private:

    // minimalna ścieżka
    vector<int> path;

    // długość minimalnej ścieżki
    int cost;


public:

    // konstruktor
    BranchAndBound0();

    // destruktor
    ~BranchAndBound0();

    // algorytm [argumenty 2 i 3 to sposób na zwrócenie więcej niż 1 parametru (zmiana parametrów poprzez referencję) ]
    void algorithmBranchAndBound0(Graph graph, vector<int>& finalPath, int& finalPathValue);

    BB0 matrixStartReduction(vector<vector<int>> graph, int verticles, int source);
    vector<vector<int>> copyGraph(vector<vector<int>> graph, int size);
    vector<bool> copyVisited(vector<bool> visited, int size);
    BB0 reducing(Graph graph, BB0 given, int source, int endVert, int firstVertex);
    bool isVisitedLeft(vector<bool> visited, int size);
};


#endif
