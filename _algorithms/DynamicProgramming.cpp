#include "DynamicProgramming.h"
using namespace std;


DynamicProgramming::DynamicProgramming() {

}


DynamicProgramming::~DynamicProgramming() {

    delete[] path;
    costTable.clear();
    pathTable.clear();
}


/*
 *  algorytm programowania dynamicznego
 *  idea programowania dynamicznego polega na zapisywaniu w pamięci minimów w zakresie podwywołań używając rekurencji
 *  kolejne podwywołania prowadzą do coraz to łatwiejszych problemów aż to trywialnych
 *  maski bitowe to sposób na tworzenie podzbiorów,
 *          przykład: podzbiór {0,2,5} w postaci bitowej wynosi 100101 [pozycje: 0, 2 i 5] czyli wartość 37
 */



int DynamicProgramming::findMinimum(int source, int set, int matrixSize, int bitMask, int newSubset) {

    int min = INT_MAX, tempMin;

    // wartość początkowa
    if (costTable[source][set] != -1)
        return costTable[source][set];

    else {

        // dla każdego miasta
        for (int i= 0; i < matrixSize; i++) {

            // wyliczenie nowej maski bitowej
            bitMask = (unsigned int)((1 << matrixSize) - 1 - (1 << i));

            // przypisanie nowego podzbioru (użycie bitowego AND)
            newSubset = (unsigned int)set & bitMask;

            // jeżeli aktualny zbiór jest inny od nowego
            if (newSubset != set) {

                // wyliczenie kosztu dla danego podwywołania i kolejne podwywołanie
                tempMin = matrix[source][i] + findMinimum(i, newSubset, matrixSize, bitMask, newSubset);

                // znalezienie minimum dla podwywołania
                if (tempMin < min) {
                    min = tempMin;
                    pathTable[source][set] = i;
                }
            }
        }
    }
    // zapamiętanie minimum
    costTable[source][set] = min;

    return min;
}



void DynamicProgramming::findPath(int start, int set, int matrixSize, int bitMask, int newSubset, int counter) {

    // wartość początkowa
    if (pathTable[start][set] == -1)
        return;

    int i = pathTable[start][set];
    path[counter] = i;
    counter++;

    // wyliczenie nowej maski bitowej
    bitMask = (int)((1 << matrixSize) - 1 - (1 << i));

    // przypisanie nowego podzbioru (użycie bitowego AND)
    newSubset = (int)set & bitMask;

    // kolejne podwywołanie
    findPath(i, newSubset, matrixSize, bitMask, newSubset, counter);
}



int DynamicProgramming::algorithmDynamicProgramming(vector<vector<int>> originalMatrix, int* bestPath) {

    // ustawianie początkowych wartości
    cost = INT_MAX;
    int matrixSize = originalMatrix.size();
    int bitMask = 0;
    int newSubset = 0;
    int counter = 1;

    // przypisanie macierzy (globalna macierz ma duży wpływ na optymalizację)
    matrix = originalMatrix;

    // rezerwowanie miejsca
    path = new int[matrixSize + 1];
    costTable.resize(matrixSize);
    pathTable.resize(matrixSize);

    for (int i = 0; i < matrixSize; i++) {

        // uzupełnianie tablicy 2d wartościami początkowymi (-1/inf)
        for (int j = 0; j < pow(2, matrixSize); j++) {
            costTable[i].push_back(-1);
            pathTable[i].push_back(-1);
        }
    }

    // przepisanie kolumny o indeksie 0 do pomocniczej macierzy
    for (int i = 0; i < matrixSize; i++)
        costTable[i][0] = originalMatrix[i][0];


    // początkowy punkt to 0
    path[0] = 0;

    // rekurencja - szukanie minimum i wypełnianie tablic
    cost = findMinimum(0, (int)(pow(2, matrixSize) - 2), matrixSize, bitMask, newSubset);


    // rekurencja - szukanie ścieżki na podstawie wypełnionej tablicy
    findPath(0, int(pow(2, matrixSize) - 2), matrixSize, bitMask, newSubset, counter);

    // końcowym miastem jest miasto początkowe
    path[matrixSize] = path[0];


    // skopiowanie optymalnej ścieżki do zwracanej
    for (int i = 0; i < matrixSize + 1; ++i)
        bestPath[i] = path[i];


    // zwrócenie minimalnego kosztu
    return cost;
}