#include "BranchAndBound2.h"

#include "BranchAndBound.h"

/*

BranchAndBound::BranchAndBound() {

}



BranchAndBound::~BranchAndBound() {

}

// TODO opisać działanie algorytmu

int l = 1;
bool ifMainPath = false;
bool s = 1;

int BranchAndBound::reduceMatrix(vector<vector<int>> matrixToReduce) {

    int min;
    int cost = 0;

    // redukcja macierzy

    //wiersze
    for (int i = 0; i < size; i++) {
        bool ifEnd = false;
        min = INT32_MAX;
        for (int z = 0; z < size; z++) {

            if (matrixToReduce[i][z] != -1 && matrixToReduce[i][z] < min) {
                min = matrixToReduce[i][z];
            }
            if (z == size - 1)
                ifEnd = true;
        }
        if (ifEnd == true) {
            for (int z = 0; z < size; z++) {
                if (matrixToReduce[i][z] != -1) {
                    matrixToReduce[i][z] -= min;
                }
            }
            if (min == INT32_MAX)
                min = 0;
            cost += min;
        }
    }

    //kolumny
    for (int z = 0; z < size; z++) {
        bool ifEnd = false;
        min = INT32_MAX;
        for (int i = 0; i < size; i++) {

            if (matrixToReduce[i][z] != -1 && matrixToReduce[i][z] < min) {
                min = matrixToReduce[i][z];
            }
            if (i == size - 1)
                ifEnd = true;
        }
        if (ifEnd == true) {
            for (int i = 0; i < size; i++) {
                if (matrixToReduce[i][z] != -1) {
                    matrixToReduce[i][z] -= min;
                }
            }
            if (min == INT32_MAX)
                min = 0;
            cost += min;
        }
    }

    return cost;
}



void BranchAndBound::findPath(vector<vector<int>> tempMatrix, int currCost, int currVertex, int level) {

    int ifEnd = true;
    int bestCost = INT32_MAX;
    int nextVertex=0;

    vector<vector<int>> edg = tempMatrix;

    vector<bool> vis;
    vis.reserve(size);

    for (int j = 0; j < size; j++) {
        vis.push_back(false);
    }

    vector<int> newCost;
    newCost.reserve(size);
    for (int i = 0; i < size; ++i) {
        newCost.push_back(INT_MAX);
    }

    vis[currVertex] = true;

    for (int j = 0; j < size; j++) {
        if (edg[currVertex][j]!=-1 && vis[j]==false)
        {
            for (int z = 0; z < size; z++)
            {
                edg[currVertex][z] = -1;
                edg[z][j] = -1;
            }
            edg[j][0] = -1;
            edg[j][currVertex] = -1;

            newCost[j] = currCost + tempMatrix[currVertex][j] + reduceMatrix(edg);
            if (newCost[j] < bestCost)
            {
                bestCost = newCost[j];
                nextVertex = j;
            }

            ifEnd = false;
        }
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                edg[i][j] = tempMatrix[i][j];
            }
        }

    }

    if (ifEnd)
    {
        if (currCost < upperBound) {
            upperBound = currCost;
            ifMainPath = true;
            l = 1;
            path[l] = currVertex;
            s = 1;
        }

        return;
    }

    if (bestCost > upperBound)
    {
        return;
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            edg[i][j] = tempMatrix[i][j];
        }
    }

    for (int z = 0; z < size; z++)
    {
        edg[currVertex][z] = -1;
        edg[z][nextVertex] = -1;
    }
    edg[nextVertex][currVertex] = -1;
    edg[nextVertex][0]=-1;

    reduceMatrix(edg);/////

    vis[nextVertex] = true;

    findPath(edg,bestCost,nextVertex, ++level);////////

    if (ifMainPath == true)
    {
        l++;
        path[l] = currVertex;
    }


    for (int i = 0; i < size; i++)
    {
        for (int y = 0; y < size; y++) {
            for (int j = 0; j < size; j++) {
                edg[y][j] = tempMatrix[y][j];
            }
        }

        if (edg[currVertex][i] != -1)
            if (newCost[i] < upperBound  && vis[i] == false) {


                for (int z = 0; z < size; z++)
                {
                    edg[currVertex][z] = -1;
                    edg[z][i] = -1;
                }
                edg[i][currVertex] = -1;
                edg[i][0] = -1;

                reduceMatrix(edg);

                bestCost = newCost[i];
                ifMainPath = false;

                findPath(edg, bestCost, i, ++level);

                ifMainPath = true;
            }
    }
}



void BranchAndBound::algorithmBranchAndBound(Graph* graph, vector<int>& finalPath, int& finalPathValue) {

    upperBound = INT_MAX;
    lowerBound = 0;

    size = graph->getSize();

    visited.reserve(size);

    copiedMatrix = graph->getMatrix();

    for (int i = 0; i < size; ++i) {
        visited.push_back(false);
    }

    lowerBound = reduceMatrix(graph->getMatrix());
    findPath(graph->getMatrix(), lowerBound, 0, 0);

    cost = upperBound;

    // zwrócenie kosztu oraz ścieżki
    finalPath = path;
    finalPathValue = cost;


    // zwolnienie pamięci
    path.clear();
    visited.clear();
    copiedMatrix.clear();
}


*/
