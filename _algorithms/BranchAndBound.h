/*
 *  algorytm podziału i ograniczeń
 *  metoda opiera się na przeszukiwaniu drzewa reprezentującego przestrzen rozwiązań problemu
 *  odcięcia redukują liczbę przeszukiwanych wierzchołków przyspieszając rozwiązanie
 *  w danej metodzie rozgałęzienia tworzą następników danego wierzchołka
 *  a ograniczenia odcinają części drzewa, w których na pewno nie ma optymalnego rozwiązania
 *  jest to metoda Depth First - po wybraniu wierzchołka z najlepszym dolnym ograniczeniem schodzi wgłąb aż do liścia
 *  dając nowe dolne ograniczenia, które mogą zamienić górne ograniczenie
 */

#ifndef PEA_P_1_BRANCHANDBOUND_H
#define PEA_P_1_BRANCHANDBOUND_H

#include "../_structures/Graph.h"

using namespace std;


class BranchAndBound {

private:

    // koszt
    int bestCost;

    // optymalna ścieżka
    int* path;

    // tymczasowa najlepsza ścieżka
    int* possiblePath;

    // tablica odwiedzonych miast
    vector<bool> visited;

    // macierz
    vector<vector<int>> thisMatrix;

    // część algorytmu
    // szukanie minimum w danym wierszu
    int minimumLine(int line, int matrixSize);

    // część algorytmu
    // rekurencja - przeszukiwanie drzewa
    void treeSearch(int lowerBound, int cost, int level, int matrixSize);


public:

    // konstruktor
    BranchAndBound();

    // destruktor
    ~BranchAndBound();

    // algorytm
    // ustawianie wartości początkowych i zaczęcie algorytmu
    int algorithmBranchAndBound(vector<vector<int>> matrix, int *bestPath);
};


#endif

