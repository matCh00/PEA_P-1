#include "DynamicProgramming.h"



DynamicProgramming::DynamicProgramming() {

    cost = INT_MAX;
    path = {};
}



DynamicProgramming::~DynamicProgramming() {

    path.clear();
    rememberCost.clear();
    rememberPath.clear();
}

// TODO opisać działanie algorytmu

int DynamicProgramming::findPath(Graph* graph, int currentVertex, int position) {

    int size = graph->getSize();
    int vertex;
    int distance = INT_MAX;

    // zwrócenie komórki oryginalnej macierzy
    if (position == shift) {
        return graph->getCell(currentVertex, 0);
    }

    // zwrócenie komórki gdy została już zmodyfikowana
    if (rememberCost[currentVertex][position] != -1) {

        return rememberCost[currentVertex][position];
    }

    // wykonanie dla wszystkich miast
    for (int nextVertex = 0; nextVertex < size; nextVertex++) {

        // wykonanie operacji AND na każdej parze bitów z podanych liczb
        if ((position & (1 << nextVertex)) == 0) {

            // wykonanie operacji OR na każdej parze bitów z podanych liczb
            int nextPosition = position | (1 << nextVertex);

            // dodanie nowej wartości do istniejącej wartości
            int newDistance = graph->getCell(currentVertex, nextVertex) + findPath(graph, nextVertex, nextPosition);

            // jeżeli nowa ścieżka jest krótsza
            if ((newDistance < distance)) {

                // przypisanie nowej ścieżki i kosztu
                distance = newDistance;
                vertex = nextVertex;
            }
        }
    }
    rememberPath[currentVertex][position] = vertex;

    return rememberCost[currentVertex][position] = distance;
}



void DynamicProgramming::algorithmDynamicProgramming(Graph* graph, vector<int> &finalPath, int &finalCost) {

    int size = graph->getSize();

    // przesunięcie bitowe ( 1 * 2 ^ graph->getSize() )
    shift = (1 << graph->getSize()) - 1;

    // tymczasowa tablica - aby dalsze wypełnianie było szybsze
    vector<int> fill;
    fill.reserve(shift + 1);
    for (int x = 0; x < 1 << size; x++)
        fill.push_back(-1);

    // rezerwowanie miejsca
    rememberPath.reserve(size);
    rememberCost.reserve(size);

    for (int i = 0; i < size; i++) {
        rememberPath.push_back(fill);
        rememberCost.push_back(fill);
    }

    // start rekurencji i zwrócenie kosztu ścieżki
    cost = findPath(graph, 0, 1);

    // znalezienie ścieźki
    getPath();

    // zwrócenie kosztu oraz ścieżki
    finalPath = path;
    finalCost = cost;
}



void DynamicProgramming::getPath() {

    // rezerwowanie miejsca
    path.reserve(rememberPath.size());

    int p;
    int i = 0;
    int currV = 0;
    int startPos = 1;

    while (true) {

        i++;

        path.push_back(currV);
        p = rememberPath[currV][startPos];

        if (p == -1)
            break;

        int nextPos = startPos | (1 << p);
        startPos = nextPos;
        currV = p;
    }
    path.push_back(0);
}