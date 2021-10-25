#include "DynamicProgramming.h"



DynamicProgramming::DynamicProgramming() {

}



DynamicProgramming::~DynamicProgramming() {

    path.clear();
}



int DynamicProgramming::recursion(Graph* graph, int currentVertex, int position) {


    int vertex;

    int size = graph->getSize();

    if (position == endPosition) {
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
        int newDistance = graph->getCell(currentVertex, nextVertex) + recursion(graph, nextVertex, nextPosition);

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

    endPosition = (1 << graph->getSize()) - 1;

    int size = graph->getSize();



    vector<int> temp;
    temp.reserve(endPosition + 1);
    for (int j = 0; j < 1 << size; j++)
        temp.push_back(-1);


    rememberPath.reserve(size);

    for (int i = 0; i < size; i++) {
        rememberPath.push_back(temp);
    }

    rememberDistance.reserve(size);

    for (int i = 0; i < size; i++) {
        rememberDistance.push_back(temp);
    }


    // start rekurencji
    cost = recursion(graph, 1, 0);


    path.reserve(50);

    // ścieżka
    int j = 0;
    int position = 1;
    int currentVertex = 0;
    int i;

    while (true) {

        path.push_back(currentVertex);  //errrrrrr
        j++;
        i = rememberPath[currentVertex][position];

        if (i == -1)
            break;

        int nextPosition = position | (1 << i);
        position = nextPosition;
        currentVertex = i;
    }
    path.push_back(0);  //errrrrrrr


    finalPath = path;
    finalCost = cost;
}