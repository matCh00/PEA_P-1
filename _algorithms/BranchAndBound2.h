// algorytm podziału i ograniczeń

#ifndef PEA_P_1_BRANCHANDBOUND_H
#define PEA_P_1_BRANCHANDBOUND_H

#include "../_structures/Graph.h"

using namespace std;


// klasa reprezentująca algorytm BB
class BranchAndBound{

private:

    // rozmiar macierzy - liczba miast
    int cities;

    // minimalna ścieżka
    int* path;

    // długość minimalnej ścieżki
    int cost;

    // dolna granica
    int lowerBound;

    // górna granica
    int upperBound;

    // tablica odwiedzonych miast
    vector<bool> visited;

    // tymczasowa skopiowana macierz
    vector<vector<int>> copiedMatrix;

    // część algorytmu - rekurencja
    void findPath(vector<vector<int>> tempMatrix, int currCost, int currVertex, int level);

    // redukowanie tymczasowej macierzy
    int reduceMatrix(vector<vector<int>> matrixToReduce);


public:

    // konstruktor
    BranchAndBound();

    // destruktor
    ~BranchAndBound();

    // algorytm [argumenty 2 i 3 to sposób na zwrócenie więcej niż 1 parametru (zmiana parametrów poprzez referencję) ]
    int algorithmBranchAndBound(vector<vector<int>> matrix, int* bestPath);
};


#endif

