#include "BranchAndBound.h"

/*

BranchAndBound::BranchAndBound() {

}



BranchAndBound::~BranchAndBound() {

}



int BranchAndBound::branchAndBound(vector<vector<int>> matrix) {

    if (currSize <= 2) {

        // zwrócenie dolnego ograniczenia / kosztu
        return lowerBound;
    }

    // wyzerowanie dolnego ograniczenia
    lowerBound = 0;
    
    // dla każdego wiersza
    for (int i = 0; i < currSize; ++i) {

        int currMin = INT_MAX;

        // sprawdzenie każdego elementu
        for (int j = 0; j < currSize; ++j) {

            // znalezienie minimum
            if (matrix[i][j] < currMin && matrix[i][j] != 0 && matrix[i][j] != -1) {

                currMin = matrix[i][j];
            }
        }

        // odjęcie odnalezionego minimum od każdego elementu
        for (int j = 0; j < currSize; ++j) {

            matrix[i][j] -= currMin;
        }

        // jeżeli nie odnaleziono minimum
        if (currMin == INT_MAX) {

            currMin = 0;
        }

        // dolne ograniczenie to suma wszystkich minimum
        lowerBound += currMin;
    }

    // dla każdej kolumny
    for (int i = 0; i < currSize; ++i) {

        int currMin = INT_MAX;

        // sprawdzenie każdego elementu
        for (int j = 0; j < currSize; ++j) {

            // znalezienie minimum
            if (matrix[j][i] < currMin && matrix[j][i] != 0 && matrix[j][i] != -1) {

                currMin = matrix[j][i];
            }
        }

        // odjęcie odnalezionego minimum od każdego elementu
        for (int j = 0; j < currSize; ++j) {

            matrix[j][i] -= currMin;
        }

        // jeżeli nie odnaleziono minimum
        if (currMin == INT_MAX) {

            currMin = 0;
        }

        // dolne ograniczenie to suma wszystkich minimum
        lowerBound += currMin;
    }


    // największe minimum
    int maxMin = 0;

    // dla każdego wiersza
    for (int i = 0; i < currSize; ++i) {

        int currMin = INT_MAX;

        // licznik zer w wierszu
        int zeroCount = 0;

        // sprawdzenie każdego elementu
        for (int j = 0; j < currSize; ++j) {

            // znalezienie minimum
            if (matrix[i][j] < currMin && matrix[i][j] != -1 && (matrix[i][j] != 0 || zeroCount > 0)) {

                currMin = matrix[i][j];
            }

            // natrafiono na 0
            if (matrix[i][j] == 0) {

                zeroCount++;
            }
        }
        zeroCount = 0;

        // szukanie największego minimum
        if (maxMin < currMin) {

            maxMin = currMin;
        }
    }

    // dla każdej kolumny
    for (int i = 0; i < currSize; ++i) {

        int currMin = INT_MAX;

        // licznik zer w wierszu
        int zeroCount = 0;

        // sprawdzenie każdego elementu
        for (int j = 0; j < currSize; ++j) {

            // znalezienie minimum
            if (matrix[j][i] < currMin && matrix[j][i] != -1 && (matrix[j][i] != 0 || zeroCount > 0)) {

                currMin = matrix[j][i];
            }

            // natrafiono na 0
            if (matrix[j][i] == 0) {

                zeroCount++;
            }
        }
        zeroCount = 0;

        // szukanie największego minimum
        if (maxMin < currMin) {

            maxMin = currMin;
        }
    }


    // redukowanie macierzy dopóki rozmiar jej jest większy od 2
    // [skracanie w zależności od wystąpienia największego minimum:
    //   kolumnę] i dodatkowo wiersz gdy w skracanej kolumnie wystąpiło 0
    //   wiersz] i dodatkowo kolumnę gdy w skracanym wierszu wystąpiło 0

    bool alreadyReduced = false;
    bool foundMaxMinInColumn = false;

    // przeszukiwanie kolumn
    for (int i = 0; i < currSize; ++i) {

        for (int j = 0; j < currSize; ++j) {

            // znaleziono maxMin w kolumnie o indeksie i
            if (matrix[j][i] == maxMin) {

                foundMaxMinInColumn = true;
            }

            // jeżeli w kolumnie wystąpiło 0 oraz maxMin
            if (matrix[j][i] == 0 && foundMaxMinInColumn) {

                // j - indeks wiersza do redukcji
                // i - indeks kolumny do redukcji

                // zablokowanie przejścia powrotnego
                matrix[i][j] = INT_MAX;


                //REDUKCJA
                reduceMatrix(matrix, j, i);

                path.push_back(j);
                path.push_back(i);

                currSize--;

                // powiększenie dolnego ograniczenia o maxMin
                lowerBound += maxMin;

                alreadyReduced = true;
            }
        }
        foundMaxMinInColumn = false;
    }


    // jeżeli jeszcze nie nastąpiła redukcja
    if (alreadyReduced == false) {

        bool foundMaxMinInRow = false;

        // przeszukiwanie wierszy
        for (int i = 0; i < currSize; ++i) {

            for (int j = 0; j < currSize; ++j) {

                // znaleziono maxMin w wierszu o indeksie i
                if (matrix[i][j] == maxMin) {

                    foundMaxMinInRow = true;
                }

                // jeżeli w wierszu wystąpiło 0 oraz maxMin
                if (matrix[i][j] == 0 && foundMaxMinInRow) {

                    // i - indeks kolumny do redukcji
                    // j - indeks wiersza do redukcji

                    // zablokowanie przejścia powrotnego
                    matrix[j][i] = INT_MAX;


                    // REDUKCJA
                    reduceMatrix(matrix, j, i);

                    path.push_back(j);
                    path.push_back(i);

                    currSize--;

                    // powiększenie dolnego ograniczenia o maxMin
                    lowerBound += maxMin;
                }
            }
            foundMaxMinInRow = false;
        }
    }

    // wykonujemy kolejny raz
    cost = branchAndBound(matrix);
}



void BranchAndBound::reduceMatrix(vector<vector<int>> tempMatrix, int row, int column) {

    // usunięcie wiersza
    tempMatrix.erase(tempMatrix.begin() + row);

    // usunięcie kolumny
    for (size_t i = 0; i < tempMatrix.size(); ++i) {
        tempMatrix[i].erase(tempMatrix[i].begin() + column);
    }
}



void BranchAndBound::algorithmBranchAndBound(Graph* graph, vector<int>& finalPath, int& finalPathValue) {

    // przypisanie rozmiaru
    size = graph->getSize();
    currSize = size;

    cost = INT_MAX;

    // rezerwowanie miejsca
    path.reserve(size);

    // skopiowanie macierzy
    tempMatrix = graph->getMatrix();

    branchAndBound(tempMatrix);


    finalPathValue = cost;
    finalPath = path;

    tempMatrix.clear();
    path.clear();
}

*/







/*


#include "BranchAndBound.h"
#include <iostream>
#include <fstream>
#include <chrono>

int l = 1;
int ifMainPath = false;
int h = 0;
bool s = 1;



BranchAndBound::BranchAndBound(Graph* chosenGraph)
{
    this->graph = chosenGraph;
    graphSize = graph.getSize();

    lowerBound = 0;
    upperBound = INT32_MAX;
}

int BranchAndBound::reduceMatrix(vector<vector<int>> redEdge)
{
    int min;
    int cost = 0;

    // redukcja macierzy

    //wiersze
    for (int i = 0; i < graphSize; i++) {
        bool ifEnd = false;
        min = INT32_MAX;
        for (int z = 0; z < graphSize; z++) {

            if (redEdge[i][z] != -1 && redEdge[i][z] < min) {
                min = redEdge[i][z];
            }
            if (z == graphSize - 1)
                ifEnd = true;
        }
        if (ifEnd == true) {
            for (int z = 0; z < graphSize; z++) {
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
    for (int z = 0; z < graphSize; z++) {
        bool ifEnd = false;
        min = INT32_MAX;
        for (int i = 0; i < graphSize; i++) {

            if (redEdge[i][z] != -1 && redEdge[i][z] < min) {
                min = redEdge[i][z];
            }
            if (i == graphSize - 1)
                ifEnd = true;
        }
        if (ifEnd == true) {
            for (int i = 0; i < graphSize; i++) {
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

void BranchAndBound::tspR(vector<vector<int>> tmpEdge, int currCost, int currVertex, int lvl)
{
    int ifEnd = true;
    int bestCost = INT32_MAX;
    int nextVertex=0;
    vector<vector<int>> edg(tmpEdge);

    //edg = tmpEdge;

    vector<bool> vis;
    vis.reserve(graphSize);

    for (int j = 0; j < graphSize; j++) {
        vis.push_back(false);
    }

    vector<int> newCost;
    newCost.reserve(graphSize);
    for (int i = 0; i < graphSize; ++i) {
        newCost.push_back(0);
    }

    vis[currVertex] = true;

    for (int j = 0; j < graphSize; j++) {
        if (edg[currVertex][j]!=-1 && vis[j]==false)
        {
            for (int z = 0; z < graphSize; z++)
            {
                edg[currVertex][z] = -1;
                edg[z][j] = -1;
            }
            edg[j][0] = -1;
            edg[j][currVertex] = -1;

            newCost[j] = currCost + tmpEdge[currVertex][j] + reduceMatrix(edg);/////
            if (newCost[j] < bestCost)
            {
                bestCost = newCost[j];
                nextVertex = j;
            }

            ifEnd = false;
        }
        for (int i = 0; i < graphSize; i++) {
            for (int j = 0; j < graphSize; j++) {
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

    for (int i = 0; i < graphSize; i++) {
        for (int j = 0; j < graphSize; j++) {
            edg[i][j] = tmpEdge[i][j];
        }
    }

    for (int z = 0; z < graphSize; z++)
    {
        edg[currVertex][z] = -1;
        edg[z][nextVertex] = -1;
    }
    edg[nextVertex][currVertex] = -1;
    edg[nextVertex][0]=-1;

    reduceMatrix(edg);

    vis[nextVertex] = true;

    tspR(edg,bestCost,nextVertex, ++lvl);

    if (ifMainPath == true)
    {
        l++;
        path[l] = currVertex;
    }


    for (int i = 0; i < graphSize; i++)
    {

        edg = tmpEdge;

        if (edg[currVertex][i] != -1)
            if (newCost[i] < upperBound  && vis[i] == false) {


                for (int z = 0; z < graphSize; z++)
                {
                    edg[currVertex][z] = -1;
                    edg[z][i] = -1;
                }
                edg[i][currVertex] = -1;
                edg[i][0] = -1;

                reduceMatrix(edg);

                bestCost = newCost[i];
                ifMainPath = false;

                tspR(edg, bestCost, i, ++lvl);

                ifMainPath = true;
            }
    }


    edg.clear();

    vis.clear();

    newCost.clear();
}

void BranchAndBound::branchNbound()
{
    vector<bool> visited;
    visited.reserve(graphSize);

    for (int j = 0; j < graphSize; j++)
        visited.push_back(false);



    lowerBound = reduceMatrix(graph.getMatrix());

    tspR(graph.getMatrix(), lowerBound, 0, 0);



    std::cout <<"Min distance: " << upperBound;

    std::cout << "\n";
    path[0] = 0;
    path[graphSize] = 0;
    std::cout << "Path: ";
    for (int i = graphSize; i > 0; i--)
    {
        std::cout << path[i] << " -> ";
    }
    std::cout << path[0];
}


BranchAndBound::~BranchAndBound()
{
}
*/




#include "BranchAndBound.h"
#include <iostream>
#include <fstream>
#include <chrono>

int l = 1;
int ifMainPath = false;
int h = 0;
bool s = 1;


using tp = std::chrono::time_point<std::chrono::system_clock>;
using duration = std::chrono::duration<float, std::milli>;

BranchAndBound::BranchAndBound(int **edge,int cities)
{
    this->edge = edge;
    this->cities = cities;
    lowerBound = 0;
    upperBound = INT32_MAX;
}

int BranchAndBound::reduceMatrix(int **redEdge)
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

void BranchAndBound::tspR(int **tmpEdge, int currCost, int currVertex, int lvl)
{
    int ifEnd = true;
    int bestCost = INT32_MAX;
    int nextVertex=0;
    int **edg = new int*[cities];

    for (int i = 0; i < cities; i++) {

        edg[i] = new int[cities];

        for (int j = 0; j < cities; j++) {
            edg[i][j]=tmpEdge[i][j];
        }
    }

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

    tspR(edg,bestCost,nextVertex, ++lvl);

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

                tspR(edg, bestCost, i, ++lvl);

                ifMainPath = true;
            }
    }


    for (int j = 0; j < cities; j++) {
        delete[] edg[j];
    }
    delete[] edg;

    delete[] vis;

    delete[] newCost;
}

void BranchAndBound::branchNbound()
{
    bool *visited = new bool[cities];

    for (int j = 0; j < cities; j++)
        visited[j] = false;

    tp start = std::chrono::system_clock::now();

    lowerBound = reduceMatrix(edge);

    tspR(edge, lowerBound, 0, 0);

    duration d = std::chrono::system_clock::now() - start;

    std::cout<<"Time: " << d.count() << "\n";

    std::cout <<"Min distance: " << upperBound;

    std::cout << "\n";
    path[0] = 0;
    path[cities] = 0;
    std::cout << "Path: ";
    for (int i = cities; i > 0; i--)
    {
        std::cout << path[i] << " -> ";
    }
    std::cout << path[0];
}


BranchAndBound::~BranchAndBound()
{
}
