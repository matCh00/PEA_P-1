// algorytm podziału i ograniczeń

#pragma once
#include "Graph.h"

using namespace std;


// klasa pomocnicza do algorytmu przechowująca wyniki redukcji
class BB {

public:
    int vertexNumber;		//numer aktualnie sprawdzanego wierzcholka
    int **graph;		//graf przechowywany w danej chwili
    int reduction;			//chwilowy koszt przejscia do danego wierzcholka po wczesniejszej sciezce
    bool *visited;			//tablica przechowujaca liste odwiedzonych wierzcholkow
    vector<int> path;   	//wektor przechowujacy kolejne wierzcholki w drodze
};



// klasa reprezentująca algorytm BB
class BranchAndBound {

private:

    // minimalna ścieżka
    vector<int> path;

    // długość minimalnej ścieżki
    int pathCost;


public:

    // konstruktor
    BranchAndBound();

    // destruktor
    ~BranchAndBound();

    bool compareByCost(const BB &a, const BB &b);
    void calculatingPath(Graph graph, int startVert, vector<int>& finalPath, int& finalPathValue);
    BB matrixStartReduction(int** graph, int verticles, int startVert);
    int** copyGraph(int**graph, int size);
    bool* copyVisited(bool*visited, int size);
    BB reducing(Graph graph, BB given, int startVert, int endVert, int firstVertex);
    bool isVisitedLeft(bool* visited, int size);
    vector<int> getPath();
};

