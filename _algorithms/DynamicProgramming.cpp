#include "DynamicProgramming.h"



DynamicProgramming::DynamicProgramming() {

    cost = INT_MAX;
    path = {};
}



DynamicProgramming::~DynamicProgramming() {

    path.clear();
    rememberDistance.clear();
    rememberPath.clear();
}



int DynamicProgramming::findPath(Graph* graph, int currentVertex, int position) {


    int vertex;

    int size = graph->getSize();

    if (position == shift) {
        return graph->getCell(currentVertex, 0);
    }

    if (rememberDistance[currentVertex][position] != -1) {

        return rememberDistance[currentVertex][position];
    }

    int distance = INT_MAX;

    for (int nextVertex = 0; nextVertex < size; nextVertex++) {

        if ((position & (1 << nextVertex)) != 0) {
            continue;
        }

        int nextPosition = position | (1 << nextVertex);

        // do istniejącej wartości dodajemy nową wartość
        int newDistance = graph->getCell(currentVertex, nextVertex) + findPath(graph, nextVertex, nextPosition);

        // jeżeli nowa ścieżka jest krótsza
        if ((newDistance < distance)) {

            // przypisanie nowej ścieżki i kosztu
            distance = newDistance;
            vertex = nextVertex;
        }

    }
    rememberPath[currentVertex][position] = vertex;

    return rememberDistance[currentVertex][position] = distance;
}



void DynamicProgramming::algorithmDynamicProgramming(Graph* graph, vector<int> &finalPath, int &finalCost) {

    int size = graph->getSize();

    //   ( 1 * 2 ^ graph->getSize() )
    shift = (1 << graph->getSize()) - 1;

    // tymczasowa tablica - aby dalsze wypełnianie było szybsze
    vector<int> fill;
    fill.reserve(shift + 1);
    for (int x = 0; x < 1 << size; x++)
        fill.push_back(-1);

    // rezerwowanie miejsca
    rememberPath.reserve(size);
    rememberDistance.reserve(size);

    for (int i = 0; i < size; i++) {
        rememberPath.push_back(fill);
        rememberDistance.push_back(fill);
    }

    // start rekurencji i zwrócenie kosztu ścieżki
    cost = findPath(graph, 0, 1);


    path.reserve(50);

    // ścieżka
    int j = 0;
    int position = 1;
    int currentVertex = 0;
    int i;

    while (true) {

        path.push_back(currentVertex);
        j++;
        i = rememberPath[currentVertex][position];

        if (i == -1)
            break;

        int nextPosition = position | (1 << i);
        position = nextPosition;
        currentVertex = i;
    }
    path.push_back(0);


    finalPath = path;
    finalCost = cost;
}