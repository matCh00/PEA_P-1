#include "BranchAndBound.h"



BranchAndBound::BranchAndBound()
{

}

BranchAndBound::~BranchAndBound()
{

}

int BranchAndBound::algorithmBranchAndBound(vector<vector<int>> matrix, int* bestPath)
{
    numberOfCities = matrix.size();


    //matrixOfDistance = matrix;
    matrixOfDistance.insert(matrixOfDistance.end(), matrix.begin(), matrix.end());

    bestResult = INT_MAX;									//upperBound
    possibleSolution = new int[numberOfCities + 1];			//obecne rozwiazanie
    solution = new int[numberOfCities + 1];
    visited = new bool[numberOfCities];

    int lowerBound = 0;

    memset(visited, 0, numberOfCities);

    for (int i = 0; i < numberOfCities; i++)
        lowerBound += minLine(i);

    visited[0] = true;
    possibleSolution[0] = 0;

    treeSearch(lowerBound, 0, 1);


    for (int i = 0; i < numberOfCities + 1; ++i) {
        bestPath[i] = solution[i];
    }



    return bestResult;
}



void BranchAndBound::toSolution()
{
    for (int i = 0; i < numberOfCities; i++)
        solution[i] = possibleSolution[i];

    solution[numberOfCities] = possibleSolution[0];
}

int BranchAndBound::minLine(int l)
{
    int min = INT_MAX;

    for (int i = 0; i < numberOfCities; i++)
        if (matrixOfDistance[l][i] < min && l != i && visited[i] == false)
            min = matrixOfDistance[l][i];
        return min;
}

void BranchAndBound::treeSearch(int lowerBound, int cost, int level)
{
    if (level == numberOfCities)
    {
        if (matrixOfDistance[possibleSolution[level - 1]][possibleSolution[0]] != (-1))
        {
            int result = cost + matrixOfDistance[possibleSolution[level - 1]][possibleSolution[0]];

            if (result < bestResult)
            {
                toSolution();
                bestResult = result;
            }
        }
        return;
    }

    for (int i = 0; i <= numberOfCities; i++)
    {
        int temp = possibleSolution[level - 1];

        if (matrixOfDistance[temp][i] != (-1) && visited[i] == false)
        {
            int temp = lowerBound;
            lowerBound = 0;

            cost += matrixOfDistance[possibleSolution[level - 1]][i];

            for (int j = 1; j < numberOfCities; j++)
            {
                if (j == i)
                    visited[0] = true;
                else
                    visited[0] = false;

                if (visited[j] == false)
                    lowerBound += minLine(j);
            }

            visited[0] = true;

            if (lowerBound + cost < bestResult)
            {
                possibleSolution[level] = i;
                visited[i] = true;

                treeSearch(lowerBound, cost, level + 1);
            }

            cost -= matrixOfDistance[possibleSolution[level - 1]][i];
            lowerBound = temp;

            memset(visited, false, numberOfCities);
            for (int j = 0; j <= level - 1; j++)
                visited[possibleSolution[j]] = true;
        }
    }

}

