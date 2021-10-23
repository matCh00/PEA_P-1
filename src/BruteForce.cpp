#include "BruteForce.h"



BruteForce::BruteForce() {

    cost = 0;
}



BruteForce::~BruteForce() {

    path.clear();
}



int BruteForce::calculatePath(Graph* graph, vector<int> cities, int size) {

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

    vector<int> cities;


    for (int i = 0; i < size; i++) {
        cities[i] = i;
    }


    sort(cities.begin(), cities.end());

    do {
        int pathCost = calculatePath(graph, cities, size);

        if (pathCost < cost) {
            cost = pathCost;

            for (int i = 0; i < size; i++) {
                path[i] = cities[i];
            }
        }

    } while (next_permutation(cities.begin(), cities.end()));



    finalPath = path;

    finalCost = cost;
}