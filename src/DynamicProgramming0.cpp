#include "DynamicProgramming0.h"



DynamicProgramming0::DynamicProgramming0() {

}



DynamicProgramming0::~DynamicProgramming0() {

    path.clear();
    cost.clear();
}



int DynamicProgramming0::recursion(Graph* graph, int visitedCities, int currentPosition) {

    if (visitedCities == visitedCount) {

        path[visitedCities][currentPosition] = {currentPosition};

        return graph->getCell(currentPosition, 0);
    }

    if (cost[visitedCities][currentPosition] != -1) {

        return cost[visitedCities][currentPosition];
    }

    int currentCost = INT_MAX;
    vector<int> currentPath = {};

    for (int city = 0; city < graph->getSize(); city++) {

        if ((visitedCities & (1 << city)) == 0) {

            // do istniejącej wartości dodajemy nową wartość
            int newCost = graph->getCell(currentPosition, city) + recursion(graph, visitedCities | (1 << city), city);

            // jeżeli nowa ścieżka jest krótsza
            if ((newCost < currentCost)) {

                // przypisanie nowej ścieżki i kosztu
                currentCost = newCost;
                currentPath = path[visitedCities | (1 << city)][city];
                currentPath.insert(currentPath.begin(), currentPosition);
            }
        }
    }

    // przypisanie optymalnej ścieżki i kosztu
    path[visitedCities][currentPosition] = currentPath;
    cost[visitedCities][currentPosition] = currentCost;

    return currentCost;
}



void DynamicProgramming0::algorithmDynamicProgramming0(Graph* graph, vector<int> &finalPath, int &finalCost) {

    int size = graph->getSize();

    // 1 * (2 ^ size)
    visitedCount = (1 << size) - 1;

    // rezerwowanie miejsca
    cost.reserve(1 << size);
    path.reserve(1 << size);

    // tworzenie dużej macierzy i wypełnianie -1
    for (int i = 0; i < (1 << size); i++) {

        vector<int> row;

        for (int j = 0; j < size; j++) {

            row.push_back(-1);
        }
        cost.push_back(row);
    }

    // tworzenie dużej macierzy, zamiast push_back(vector<int>) mamy emplace_back(int)
    for (int i = 0; i < (1 << size); i++) {
        vector<vector<int>> row;

        for (int j = 0; j < size; j++) {

            // emplace umożliwia dodanie tylko argumentów konstruktora obiektu a nie całego obiektu
            row.emplace_back(0);
        }
        path.push_back(row);
    }

    // start rekurencji
    recursion(graph, 1, 0);

    // dodanie na ostatnią pozycję początkowe miasto
    path[1][0].push_back(0);


    // zwrócenie kosztu oraz ścieżki
    finalCost = cost[1][0];
    finalPath = path[1][0];
}