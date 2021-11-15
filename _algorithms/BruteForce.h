/*
 *  algorytm przeglądu zupełnego
 *  gwarantuje optymalne wyniki ale jest bardzo wolny
 *  polega na permutacjach, sprawdza wszystkie możliwe ścieżki
 */

#ifndef PEA_P_1_BRUTEFORCE_H
#define PEA_P_1_BRUTEFORCE_H

#include "../_structures/Graph.h"

using namespace std;


// klasa reprezentująca algorytm BF
class BruteForce {

private:

    // macierz
    vector<vector<int>> matrix;

    // wielkość macierzy
    int matrixSize;

    // część algorytmu - policzenie pojedynczej ścieżki
    int calculate(int* nodes);


public:

    // konstruktor
    BruteForce();

    // destruktor
    ~BruteForce();

    // algorytm - permutacje
    // zwraca koszt, ścieżka jest zwracana jako drugi argument funkcji
    int algorithmBruteForce(vector<vector<int>> matrix, int* bestPath);
};


#endif
