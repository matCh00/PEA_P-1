#include "DynamicProgramming.h"
using namespace std;


DynamicProgramming::DynamicProgramming() {

}


DynamicProgramming::~DynamicProgramming() {

    delete[] path;
    nodeValues.clear();
    possiblePath.clear();
}


/*
 *  algorytm programowania dynamicznego
 *  idea programowania dynamicznego polega na zapisywaniu w pamięci minimów w zakresie podwywołań używając rekurencji
 *  kolejne podwywołania prowadzą do coraz to łatwiejszych problemów aż to trywialnych
 *  maski bitowe to sposób na tworzenie podzbiorów,
 *          przykład: podzbiór {0,2,5} w postaci bitowej wynosi 100101 [pozycje: 0, 2 i 5] czyli wartość 37
 */



int DynamicProgramming::findMinimum(int source, int set, vector<vector<int>> matrix, int &counter, int &bitMask, int &newSubset) {

    int min = INT_MAX, tempMin;
    counter++;

    // wartość początkowa
    if (nodeValues[source][set] != -1)
        return nodeValues[source][set];

    else {

        // dla każdego miasta
        for (int i= 0; i < matrixSize; i++) {

            // wyliczenie nowej maski bitowej
            bitMask = (int)(pow(2, matrixSize) - 1 - pow(2, i));

            // przypisanie nowego podzbioru (użycie bitowego AND)
            newSubset = (int)set & bitMask;

            // jeżeli aktualny zbiór jest inny od nowego
            if (newSubset != set) {

                // wyliczenie kosztu
                tempMin = matrix[source][i] + findMinimum(i, newSubset, matrix, counter,bitMask,newSubset);

                // jeżeli nowy koszt jest mniejszy od aktualnego
                if (tempMin < min) {
                    min = tempMin;
                    possiblePath[source][set] = i;

                }
            }
        }
    }
    // zapamiętanie minimum
    nodeValues[source][set] = min;

    return min;
}



void DynamicProgramming::findPath(int start, int set, int &counter, int &bitMask, int &newSubset) {

    // wartość początkowa
    if (possiblePath[start][set] == -1)
        return;

    int i = possiblePath[start][set];
    path[counter] = i;
    counter++;

    // wyliczenie nowej maski bitowej
    bitMask = (int)(pow(2, matrixSize) - 1 - pow(2, i));

    // przypisanie nowego podzbioru (użycie bitowego AND)
    newSubset = (int)set & bitMask;

    // rekurencja o nowych argumentach
    findPath(i, newSubset,counter,bitMask,newSubset);
}



int DynamicProgramming::algorithmDynamicProgramming(vector<vector<int>> matrix, int* bestPath) {

    // ustawianie początkowych wartości
    int min = INT_MAX;
    matrixSize = matrix.size();
    int bitMask = 0, newSubset = 0, counter = 0;

    // rezerwowanie miejsca
    path = new int[matrixSize + 1];
    nodeValues.resize(matrixSize);
    possiblePath.resize(matrixSize);

    // rezerwowanie miejsca
    for (int i = 0; i < matrixSize; i++) {
        nodeValues.resize((int)pow(2, matrixSize));
        possiblePath.resize((int)pow(2, matrixSize));

        // uzupełnianie tablicy 2d wartościami początkowymi (-1/inf)
        for (int j = 0; j < pow(2, matrixSize); j++) {
            nodeValues[i].push_back(-1);
            possiblePath[i].push_back(-1);
        }
    }

    // przepisanie kolumny o indeksie 0 do pomocniczej macierzy
    for (int i = 0; i < matrixSize; i++)
        nodeValues[i][0] = matrix[i][0];


    // początkowy punkt to 0
    path[0] = 0;

    // rekurencja - szukanie minimum
    min = findMinimum(0, (int)(pow(2, matrixSize) - 2), matrix,counter,bitMask,newSubset);
    counter = 1;

    // rekurencja - szukanie ścieżki
    findPath(0, int(pow(2, matrixSize) - 2),counter,bitMask,newSubset);

    // końcowym miastem jest miasto początkowe
    path[matrixSize] = path[0];


    // skopiowanie optymalnej ścieżki do zwracanej
    for (int i = 0; i < matrixSize + 1; ++i)
        bestPath[i] = path[i];

    // zwrócenie minimalnego kosztu
    return min;
}