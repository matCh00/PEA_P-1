#include "BranchAndBound.h"



BranchAndBound::BranchAndBound() {

    pathValue = 0;
    pathOfCities = {};
}



BranchAndBound::~BranchAndBound() {

    pathOfCities.clear();
}



int BranchAndBound::reduceGraph(int **distances) {

    int minCost = 0;

    vector<int> minRowCost;
    vector<int> minColCost;

    int minRow = INT_MAX;

    for (int i = 0; i < sizeof distances; i++)
    {
        for (int j = 0; j < sizeof distances; j++)
        {
            if (distances[i][j] != 0 && distances[i][j] < minRow)
            {
                minRow = distances[i][j];
            }
        }


        minRowCost.push_back(minRow);

        for (int j = 0; j < sizeof distances; j++)
        {
            if (i != j && distances[i][j] != 0)
            {
                distances[i][j] -= minRowCost[i];
            }

        }

        minRow = INT_MAX;
    }

    int minCol = INT_MAX;

    for (int i = 0; i < sizeof distances; i++)
    {
        for (int j = 0; j < sizeof distances; j++)
        {
            if (distances[j][i] != 0 && distances[j][i] < minCol)
            {
                minCol = distances[j][i];
            }
        }

        minColCost.push_back(minCol);

        for (int j = 0; j < sizeof distances; j++)
        {
            if (i != j && distances[j][i] != 0)
            {
                distances[j][i] -= minColCost[i];
            }

        }

        minCol = INT_MAX;
    }

    for (int i = 0; i < sizeof distances; i++)
    {
        if (minRowCost[i] == INT_MAX)
        {
            minRowCost[i] = 0;
        }
        if (minColCost[i] == INT_MAX)
        {
            minColCost[i] = 0;
        }

        minCost += minColCost[i] + minRowCost[i];
    }

    return minCost;
}


int** BranchAndBound::markStep(int row, int col, int **distances) {

    int ** temp = distances;

    for (int i = 0; i < sizeof temp; i++)
    {
        temp[row][i] = 0;
        temp[i][col] = 0;
    }

    temp[col][row] = 0;

    return temp;
}


void BranchAndBound::algorithmBranchAndBound(Graph graph, int source, vector<int> &finalPath, int &finalPathValue) {

    BB city = new BB();

    //kolejka struktur
    priority_queue<city> pq;

    pathValue = INT_MAX;
    city.weight = INT_MAX;
    currentGraph = graph.getDistances();

    city.bound = source;
    city.weight = ReduceGraph(currentGraph);
    city.currentGraphBB = currentGraph;

    pq.push(city);

    do
    {
        BB currCity;

        //odwolanie do pierwszego elementu z kloejki
        currCity = pq.top();
        if (currCity.bound == source)
        {
            currCity.path.push_back(source);
        }

        //usuniecie pobranego elemntu
        pq.pop();
        currCity.visited.resize(this->vertex);
        currCity.visited[currCity.bound] = true;

        for(int i = 0; i < this->vertex; i++)
        {
            //sprawdzenie czy dany wierzchołek nie byłjuż odwiedzony
            if(!currCity.visited[i])
            {
                BB newCity;
                //iniclajizacja zmiennych ze struktury zgodnie z algorytmem
                newCity.currentGraphBB = MakeInf(currCity.bound, i, currCity.currentGraphBB);
                newCity.visited = currCity.visited;
                newCity.path = currCity.path;
                newCity.bound = i;
                newCity.path.push_back(i);
                newCity.visited[i] = true;

                newCity.weight = currCity.currentGraphBB[currCity.bound][i] + currCity.weight + ReduceGraph(newCity.currentGraphBB);

                //dodanie wierzchołków do kolejki
                pq.push(newCity);
            }
        }
        this->pathValue = currCity.weight;
        this->pathOfCities = currCity.path;
    }
    while (path.size() < this->vertex);

    pathOfCities.push_back(source);

    return city;
}