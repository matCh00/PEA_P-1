#include "BruteForce.h"



BruteForce::BruteForce() {

    cost = 0;
}



BruteForce::~BruteForce() {

    path.clear();
}



int BruteForce::calculatePath(Graph* graph, int cities[], int size) {

    int sum = 0;

    for (int i = 0; i < size-1; i++) {
        int p = graph->getCell(cities[i], cities[i+1]);
        sum += p;
    }
    sum += graph ->getCell(cities[size-1], cities[0]);

    return sum;
}



void BruteForce::algorithmBruteForce(Graph* graph, vector<int> &finalPath, int &finalCost) {

    int size = graph->getSize();

    int* cities = new int[size];


    for (int i = 0; i < size; i++) {
        cities[i] = i;
    }

    int* pathArr = new int[size];


    sort(cities, cities + size);

    do {
        int path = calculatePath(graph, cities, size);
        if (path < cost) {
            cost = path;

            for (int i = 0; i < size; i++) {
                pathArr[i] = cities[i];
            }
        }

    } while (next_permutation(cities, cities + size));


    // konwersja array to vector
    vector<int> temp(pathArr, pathArr + sizeof(pathArr) / sizeof(int));
    path = temp;
    finalPath = path;

    finalCost = cost;
}