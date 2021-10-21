#include "BruteForce.h"



BruteForce::BruteForce() {

    cost = 0;
    path = {};
}



BruteForce::~BruteForce() {

    path.clear();
}


//TODO dokładniej ogarnąć jak działa algorytm i komentować to
void BruteForce::algorithmBruteForce(Graph graph, int source, vector<int>& finalPath, int& finalCost) {

    // miasta
    vector<int> nodes;

    // aktualna ścieżka
    vector<int> currentPath;

    // minimalna ścierzka
    cost = INT_MAX;

    // dodawanie miast do wektora oprócz pierwszego
    for (int i = 1; i < graph.getSize(); ++i) {

        nodes.push_back(i);
    }


    do {
        // dodanie wierzchołka startowego do wektora ze ścieżką
        currentPath.push_back(source);

        int currentPathCost = 0;
        int temp = source;

        // obliczanie wag i dróg dla danych wierzchołków
        for (size_t i = 0; i < nodes.size(); ++i) {

            // dodanie dystansu
            currentPathCost += graph.getMatrix()[temp][nodes[i]];

            // przejście do następnego miasta
            temp = nodes[i];

            // dodanie miasta do ścieżki
            currentPath.push_back(temp);
        }


        // dodanie dystansu
        currentPathCost += graph.getMatrix()[temp][source];


        // dodanie miasta do ścieżki
        currentPath.push_back(source);


        // sprawdzenie wag
        if (currentPathCost < cost) {

            // zmiana wartości ścieżki
            cost = currentPathCost;

            // aktualizacja ścieżki
            path = currentPath;
        }
        else {

            // usunięcie ścieżki
            currentPath.clear();
        }

        cost = min(cost, currentPathCost);

      // warunek póki nie zostana wyliczone wszystkie mozliwe kombinacje
    } while (next_permutation(nodes.begin(), nodes.end()));



    // zwrócenie ścieżki jako argumentu funkcji
    finalPath = path;

    // zwrócenie długości ścieżki jako argumentu funkcji
    finalCost = cost;
}