#include "BruteForce.h"



BruteForce::BruteForce() {

    cost = INT_MAX;
    path = {};
}



BruteForce::~BruteForce() {

    path.clear();
}



int BruteForce::calculatePath(Graph* graph, vector<int> cities, int size) {

    int sum = 0;

    for (int i = 0; i < size - 1; i++) {

        // zliczanie sumy ścieżek
        sum += graph->getCell(cities[i], cities[i+1]);
    }

    // doliczenie ścieżki z ostatniego miasta do pierwszego
    sum += graph ->getCell(cities[size-1], cities[0]);

    return sum;
}



void BruteForce::algorithmBruteForce(Graph* graph, vector<int> &finalPath, int &finalCost) {

    int size = graph->getSize();

    // badana ścieżka
    vector<int> cities;
    cities.reserve(size);

    for (int i = 0; i < graph->getSize(); i++)
        cities.push_back(i);

    // sortowanie miast
    sort(cities.begin(), cities.end());

    do {

        // wyliczenie optymalnej ścieżki dla zbioru miast
        int pathCost = calculatePath(graph, cities, size);

        // jeżeli koszt jest mniejszy od dotychczasowego
        if (pathCost < cost) {

            // znaleziono nową najkrótszą ścieżkę
            cost = pathCost;
            path.clear();
            path = cities;
        }

      // sprawdza wszystkie możliwe kombinacje
    } while (next_permutation(cities.begin(), cities.end()));

    // dodanie początkowego elementu na koniec
    path.push_back(path[0]);

    // zwraca koszt oraz ścieżkę
    finalCost = cost;
    finalPath = path;
}