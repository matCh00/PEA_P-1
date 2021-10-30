// algorytm podziału i ograniczeń

#ifndef PEA_P_1_BRANCHANDBOUND_H
#define PEA_P_1_BRANCHANDBOUND_H
/*
#include "../_structures/Graph.h"

using namespace std;


// klasa reprezentująca algorytm BB
class BranchAndBound{

private:

    // minimalna ścieżka
    vector<int> path;

    // długość minimalnej ścieżki
    int cost;

    // szukanie minimum i odjęcie go od wierszy/kolumn
    // wyznaczenie dolnego ograniczenia
    // wyznaczenie minimum dla każdego wiersza i kolumny
    // wyznaczenie maximum spośród wszystkich minimum
    // tworzenie nowej macierzy kosztów
    // obliczenie nowego dolnego ograniczenia
    // redukowanie macierzy
    int branchAndBound(vector<vector<int>> matrix);

    // redukcja macierzy
    void reduceMatrix(vector<vector<int>> tempMatrix, int row, int column);

    // dolne ograniczenie
    int lowerBound;

    // rozmiar macierzy
    int size;

    // tymczasowy rozmiar redukowanej macierzy
    int currSize;

    // tymczasowa macierz
    vector<vector<int>> tempMatrix;

    //


public:

    // konstruktor
    BranchAndBound();

    // destruktor
    ~BranchAndBound();

    // algorytm [argumenty 2 i 3 to sposób na zwrócenie więcej niż 1 parametru (zmiana parametrów poprzez referencję) ]
    void algorithmBranchAndBound(Graph* graph, vector<int>& finalPath, int& finalPathValue);
};

*/






/*

#include "../_structures/Graph.h"

class BranchAndBound
{
    Graph graph;
    int graphSize;

    //vector<vector<int>> edge;
    //int cities;

    int lowerBound;
    int upperBound;
    int minTourCost;

    int path[40];

public:
    BranchAndBound(Graph* chosenGraph);

    void tspR(vector<vector<int>> edge, int currCost, int currVertex, int lvl);
    void branchNbound();
    int reduceMatrix(vector<vector<int>> redEdge);
    ~BranchAndBound();
};

*/






class BranchAndBound
{
    int cities;
    int lowerBound;
    int upperBound;
    int minTourCost;
    int **edge;
    int path[40];

public:
    BranchAndBound(int **edge, int cities);

    void tspR(int **edge, int currCost, int currVertex, int lvl);
    void branchNbound();
    int reduceMatrix(int **redEdge);
    ~BranchAndBound();
};

#endif

