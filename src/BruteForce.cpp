#include "BruteForce.h"



BruteForce::BruteForce() {

    pathValue = 0;
    pathOfCities = {};
}



BruteForce::~BruteForce() {

    pathOfCities.clear();
}


//TODO dokładniej ogarnąć jak działa algorytm i komentować to
void BruteForce::algorithmBruteForce(Graph graph, int source, vector<int>& finalPath, int& finalPathValue) {

    // miasta
    vector<int> cities;

    // aktualna ścieżka
    vector<int> currentPath;

    // minimalna ścierzka
    pathValue = INT_MAX;

    // dodawanie miast do wektora oprócz pierwszego
    for (int i = 1; i < graph.getCities(); ++i) {

        cities.push_back(i);
    }


    do {
        // dodanie wierzchołka startowego do wektora ze ścieżką
        currentPath.push_back(source);

        int valueOfCurrentPath = 0;
        int temp = source;

        // obliczanie wag i dróg dla danych wierzchołków
        for (int i = 0; i < cities.size(); ++i) {

            // dodanie dystansu
            valueOfCurrentPath += graph.getDistances()[temp][cities[i]];

            // przejście do następnego miasta
            temp = cities[i];

            // dodanie miasta do ścieżki
            currentPath.push_back(temp);
        }


        // dodanie dystansu
        valueOfCurrentPath += graph.getDistances()[temp][source];


        // dodanie miasta do ścieżki
        currentPath.push_back(source);


        // sprawdzenie wag
        if (valueOfCurrentPath < pathValue) {

            // zmiana wartości ścieżki
            pathValue = valueOfCurrentPath;

            // aktualizacja ścieżki
            pathOfCities = currentPath;
        }
        else {

            // usunięcie ścieżki
            currentPath.clear();
        }

        pathValue = min(pathValue, valueOfCurrentPath);

      // warunek póki nie zostana wyliczone wszystkie mozliwe kombinacje
    } while (next_permutation(cities.begin(), cities.end()));



    // zwrócenie ścieżki jako argumentu funkcji
    finalPath = pathOfCities;

    // zwrócenie długości ścieżki jako argumentu funkcji
    finalPathValue = pathValue;
}