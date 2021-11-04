/*
 *  algorytm programowania dynamicznego
 *  idea programowania dynamicznego polega na zapisywaniu w pamięci minimów w zakresie podwywołań używając rekurencji
 *  kolejne podwywołania prowadzą do coraz to łatwiejszych problemów aż to trywialnych
 *  maski bitowe to sposób na tworzenie podzbiorów,
 *          przykład: podzbiór {0,2,5} w postaci bitowej wynosi 100101 [pozycje: 0, 2 i 5] czyli wartość 37
 */

#ifndef PEA_P_1_DYNAMICPROGRAMMING_H
#define PEA_P_1_DYNAMICPROGRAMMING_H

#include "../_structures/Graph.h"

using namespace std;


class DynamicProgramming {

private:

    // optymalna ścieżka
    int* path;

    // minimalny koszt
    int cost;

    // zliczanie wywołań rekurencji
    int counter;

    // macierz
    vector<vector<int>> matrix;

    // pomocnicza macierz kosztów do podzbiorów
    vector<vector<int>> costTable;

    // możliwa trasa
    vector<vector<int>> pathTable;

    // część algorytmu - znalezienie minimum
    // wykorzystując rekurencję zapisujemy kolejne minima i upraszczamy problem
    int findMinimum(int source, int set, int matrixSize, int bitMask, int newSubset);

    // część algorytmu - znalezienie ścieźki
    // wykorzystując rekurencję poruszamy się po tabeli kolejnych wierzchołków aby odtworzyć ścieżkę
    void findPath(int start, int set, int matrixSize, int bitMask, int newSubset, int counter);


public:

    // konstruktor
    DynamicProgramming();

    // destruktor
    ~DynamicProgramming();

    // algorytm główny
    // przekazanie danych, ustawienie początkowych wartości i rozpoczęcie algorytmu
    int algorithmDynamicProgramming(vector<vector<int>> originalMatrix, int* bestPath);
};


#endif
