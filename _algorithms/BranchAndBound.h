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

    // szukanie minimum i odjęcie go od wierszy/kolumn
    // wyznaczenie dolnego ograniczenia
    // wyznaczenie minimum dla każdego wiersza i kolumny
    // wyznaczenie maximum spośród wszystkich minimum
    // tworzenie nowej macierzy kosztów
    // obliczenie nowego dolnego ograniczenia
    // redukowanie macierzy
    void branchAndBound(vector<vector<int>> matrix);

    // redukcja macierzy
    void reduceMatrix(vector<vector<int>> tempMatrix, int maximum);

    // dolne ograniczenie
    int lowerBound;

    // rozmiar macierzy
    int size;

    // tymczasowa macierz
    vector<vector<int>> tempMatrix;


public:

    // konstruktor
    BranchAndBound();

    // destruktor
    ~BranchAndBound();

    // algorytm [argumenty 2 i 3 to sposób na zwrócenie więcej niż 1 parametru (zmiana parametrów poprzez referencję) ]
    void algorithmBranchAndBound(Graph* graph, vector<int>& finalPath, int& finalPathValue);
};


#endif

