#include "BruteForce.h"



BruteForce::BruteForce() : valueOfMinPath(0) {

}



BruteForce::~BruteForce() {

}



int BruteForce::algorithmBruteForce(Graph graph, int source) {

    // miasta
    vector<int> cities;

    // aktualna ścieżka
    vector<int> currentPath;

    // minimalna ścierzka
    valueOfMinPath = INT_MAX;

    // dodawanie miast do wektora oprócz pierwszego
    for (int i = 1; i < graph.numberOfCities; ++i) {

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
            valueOfCurrentPath += graph.distancesBetweenCities[temp][cities[i]];

            // przejście do następnego miasta
            temp = cities[i];

            // dodanie miasta do ścieżki
            currentPath.push_back(temp);
        }


        // dodanie dystansu
        valueOfCurrentPath += graph.distancesBetweenCities[temp][source];


        // dodanie miasta do ścieżki
        currentPath.push_back(source);


        // sprawdzenie wag
        if (valueOfCurrentPath < valueOfMinPath) {

            // zmiana wartości ścieżki
            valueOfMinPath = valueOfCurrentPath;

            // aktualizacja ścieżki
            path = currentPath;
        }
        else {

            // usunięcie ścieżki
            currentPath.clear();
        }

        valueOfMinPath = min(valueOfMinPath, valueOfCurrentPath);

      // warunek póki nie zostana wyliczone wszystkie mozliwe kombinacje
    } while (next_permutation(cities.begin(), cities.end()));


    for (int i = 0; i < path.size(); ++i) {

        if (i == path.size() - 1)
            cout << path[i];
        else
            cout << path[i] << "->";
    }
    cout << endl;

    return valueOfMinPath;
}