#include "BruteForce.h"



BruteForce::BruteForce() : countMinPath(0) {

    path.resize(numberOfCities);
}



BruteForce::~BruteForce() {

    path.clear();
}



int BruteForce::algorithmBruteForce(int source) {

    // wszystkie miasta
    vector<int> allCities;

    // aktualna ścierzka
    vector<int> currentPath;

    // minimalna ścierzka
    countMinPath = INT_MAX;

    // dodawanie miast do wektora
    for (int i = 0; i < numberOfCities; ++i) {

        // oprócz pierwszego
        if (i != source)
            allCities.push_back(i);
    }


    do {
        // dodanie wierzchołka startowego do wektora ze ścieżką
        currentPath.push_back(source);

        int weight = 0;
        int temp = source;

        // obliczanie wag i dróg dla danych wierzchołków
        for (int i = 0; i < allCities.size(); ++i) {

            // dodanie dystansu
            weight += distancesBetweenCities[temp][allCities[i]];

            // przejście do następnego miasta
            temp = allCities[i];

            // dodanie miasta do ścieżki
            currentPath.push_back(temp);
        }

        // dodanie dystansu
        weight += distancesBetweenCities[temp][source]; //!!!!!!!!!!!!

        // dodanie miasta do ścieżki
        currentPath.push_back(source);


        // sprawdzenie wag
        if (weight < countMinPath) {

            // zmiana wartości ścieżki
            countMinPath = weight;

            // aktualizacja ścieżki
            path = currentPath;
        }
        else {

            // usunięcie ścieżki
            currentPath.clear();
        }

        countMinPath = min(countMinPath, weight);

      // warunek póki nie zostana wyliczone wszystkie mozliwe kombinacje
    } while (next_permutation(allCities.begin(), allCities.end()));


    for (int i = 0; i < path.size(); ++i) {
        if (i == path.size() - 1)
            cout << path[i];
        else
            cout << path[i] << "->";
    }
    cout << endl;

    return countMinPath;
}