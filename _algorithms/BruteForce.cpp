#include "BruteForce.h"
using namespace std;


BruteForce::BruteForce() {

}


BruteForce::~BruteForce() {

}


/*
 *  algorytm przeglądu zupełnego
 *  gwarantuje optymalne wyniki ale jest bardzo wolny
 *  polega na permutacjach, sprawdza wszystkie możliwe ścieżki
 */



int BruteForce::calculate(int* nodes, vector<vector<int>> matrix) {

    int sum = 0;
    int a, b;

    for (int i = 0; i < matrix.size() - 1; i++) {

        // przypisanie miast
        a = nodes[i];
        b = nodes[i + 1];

        // zliczanie sumy ścieżek
        sum += matrix[a][b];
    }

    // doliczenie ścieżki z ostatniego miasta do pierwszego
    sum += matrix[b][nodes[0]];

    return sum;
}



int BruteForce::algorithmBruteForce(vector<vector<int>> matrix, int* bestPath) {

    // wartości początkowe
    int minCost = INT_MAX;
    int* nodes = new int[matrix.size() + 1];


    // wierzchołki
    for (int i = 0; i < matrix.size(); i++)
        nodes[i] = i;


    do {
        // obliczamy ścieżkę
        int currentCost = calculate(nodes, matrix);

        // jeżeli koszt jest mniejszy od dotychczasowego
        if (currentCost < minCost) {

            // znaleziono nową najkrótszą ścieżkę
            minCost = currentCost;

            // przypisanie ścieżki
            for (int i = 0; i < matrix.size(); ++i) {
                bestPath[i] = nodes[i];
            }
        }

      // sprawdzenie wszystkich możliwych kombinacji
    } while (next_permutation(nodes, nodes + matrix.size()));

    // dodanie zera na koniec
    bestPath[matrix.size()] = nodes[0];

    // zwrócenie kosztu
    return minCost;
}