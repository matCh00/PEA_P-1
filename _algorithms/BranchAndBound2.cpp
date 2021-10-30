#include "BranchAndBound2.h"



BranchAndBound::BranchAndBound()
{

}

int l = 1;
int ifMainPath = false;
int h = 0;
bool s = 1;



int BranchAndBound::reduceMatrix(vector<vector<int>> redEdge)
{
    int min;
    int cost = 0;

    // redukcja macierzy

    //wiersze
    for (int i = 0; i < cities; i++) {
        bool ifEnd = false;
        min = INT32_MAX;
        for (int z = 0; z < cities; z++) {

            if (redEdge[i][z] != -1 && redEdge[i][z] < min) {
                min = redEdge[i][z];
            }
            if (z == cities - 1)
                ifEnd = true;
        }
        if (ifEnd == true) {
            for (int z = 0; z < cities; z++) {
                if (redEdge[i][z] != -1) {
                    redEdge[i][z] -= min;
                }
            }
            if (min == INT32_MAX)
                min = 0;
            cost += min;
        }
    }

    //kolumny
    for (int z = 0; z < cities; z++) {
        bool ifEnd = false;
        min = INT32_MAX;
        for (int i = 0; i < cities; i++) {

            if (redEdge[i][z] != -1 && redEdge[i][z] < min) {
                min = redEdge[i][z];
            }
            if (i == cities - 1)
                ifEnd = true;
        }
        if (ifEnd == true) {
            for (int i = 0; i < cities; i++) {
                if (redEdge[i][z] != -1) {
                    redEdge[i][z] -= min;
                }
            }
            if (min == INT32_MAX)
                min = 0;
            cost += min;
        }
    }

    return cost;
}

void BranchAndBound::findPath(vector<vector<int>> tmpEdge, int currCost, int currVertex, int lvl)
{
    int ifEnd = true;
    int bestCost = INT32_MAX;
    int nextVertex=0;

    vector<vector<int>> edg;
    edg = tmpEdge;

    bool*vis = new bool[cities];

    for (int j = 0; j < cities; j++) {
        vis[j] = false;
    }

    int *newCost = new int[cities];

    vis[currVertex] = true;

    for (int j = 0; j < cities; j++) {
        if (edg[currVertex][j]!=-1 && vis[j]==false)
        {
            for (int z = 0; z < cities; z++)
            {
                edg[currVertex][z] = -1;
                edg[z][j] = -1;
            }
            edg[j][0] = -1;
            edg[j][currVertex] = -1;

            newCost[j] = currCost + tmpEdge[currVertex][j] + reduceMatrix(edg);
            if (newCost[j] < bestCost)
            {
                bestCost = newCost[j];
                nextVertex = j;
            }

            ifEnd = false;
        }
        for (int i = 0; i < cities; i++) {
            for (int j = 0; j < cities; j++) {
                edg[i][j] = tmpEdge[i][j];
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

    for (int i = 0; i < cities; i++) {
        for (int j = 0; j < cities; j++) {
            edg[i][j] = tmpEdge[i][j];
        }
    }

    for (int z = 0; z < cities; z++)
    {
        edg[currVertex][z] = -1;
        edg[z][nextVertex] = -1;
    }
    edg[nextVertex][currVertex] = -1;
    edg[nextVertex][0]=-1;

    reduceMatrix(edg);

    vis[nextVertex] = true;

    findPath(edg,bestCost,nextVertex, ++lvl);

    if (ifMainPath == true)
    {
        l++;
        path[l] = currVertex;
    }


    for (int i = 0; i < cities; i++)
    {
        for (int y = 0; y < cities; y++) {
            for (int j = 0; j < cities; j++) {
                edg[y][j] = tmpEdge[y][j];
            }
        }

        if (edg[currVertex][i] != -1)
            if (newCost[i] < upperBound  && vis[i] == false) {


                for (int z = 0; z < cities; z++)
                {
                    edg[currVertex][z] = -1;
                    edg[z][i] = -1;
                }
                edg[i][currVertex] = -1;
                edg[i][0] = -1;

                reduceMatrix(edg);

                bestCost = newCost[i];
                ifMainPath = false;

                findPath(edg, bestCost, i, ++lvl);

                ifMainPath = true;
            }
    }

    edg.clear();

    delete[] vis;

    delete[] newCost;
}

int BranchAndBound::algorithmBranchAndBound(vector<vector<int>> matrix, int* bestPath)
{
    this->cities = matrix.size();
    lowerBound = 0;
    upperBound = INT32_MAX;

    path = new int [cities + 1];

    bool *visited = new bool[cities];

    for (int j = 0; j < cities; j++)
        visited[j] = false;


    lowerBound = reduceMatrix(matrix);

    findPath(matrix, lowerBound, 0, 0);



    path[0] = 0;
    path[cities] = 0;

    bestPath = path;

    return upperBound;
}


BranchAndBound::~BranchAndBound()
{
}