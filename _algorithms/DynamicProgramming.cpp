#include "DynamicProgramming.h"
using namespace std;


DynamicProgramming::DynamicProgramming() {

}


DynamicProgramming::~DynamicProgramming() {

}

/*
 *  algorytm programowania dynamicznego
 */



int DynamicProgramming::getMinimum(int firstNode, int set, vector<vector<int>> matrix, vector<vector<int>>&tabNodeValues, vector<vector<int>>&possibleRouteTab, int &c, int &bitMask, int &newSubset) {

    int min = INT_MAX, tempMin;
    c++;
    if (tabNodeValues[firstNode][set] != -1) {
        return tabNodeValues[firstNode][set];
    }
    else {
        for (int i= 0; i < matrixSize; i++) {
            bitMask = (int)(pow(2, matrixSize) - 1 - pow(2, i));
            newSubset = (int)set & bitMask;

            if (newSubset != set) {
                tempMin = matrix[firstNode][i] + getMinimum(i, newSubset, matrix, tabNodeValues, possibleRouteTab,c,bitMask,newSubset);	// c(start,x) + g(x,S-{x}) = Cij + G(j, S-{j})
                if (tempMin < min) { //minimalizacja w zakresie podwywolania
                    min = tempMin;
                    possibleRouteTab[firstNode][set] = i;

                }
            }
        }
    }
    tabNodeValues[firstNode][set] = min;
    return min;
}



void DynamicProgramming::findPath(int start, int set, vector<vector<int>>&possibleRouteTab,int*bestPath, int &c, int &bitMask, int &newSubset) {

    if (possibleRouteTab[start][set] == -1) {
        return;
    }

    int i = possibleRouteTab[start][set];
    bestPath[c] = i;
    c++;

    bitMask = (int)(pow(2, matrixSize) - 1 - pow(2, i));
    newSubset = (int)set & bitMask;

    findPath(i, newSubset, possibleRouteTab,bestPath,c,bitMask,newSubset);
}



int DynamicProgramming::algorithmDynamicProgramming(vector<vector<int>> matrix, int* bestPath) {

    int min = INT_MAX;

    matrixSize = matrix.size();

    vector<vector<int>> tabNodeValues;
    vector<vector<int>> possibleRouteTab;

    tabNodeValues.resize(matrixSize);
    possibleRouteTab.resize(matrixSize);

    for (int i = 0; i < matrixSize; i++) {

        tabNodeValues.resize((int)pow(2, matrixSize));
        possibleRouteTab.resize((int)pow(2, matrixSize));

        for (int j = 0; j < pow(2, matrixSize); j++) {

            tabNodeValues[i].push_back(-1);
            possibleRouteTab[i].push_back(-1);
        }
    }

    for (int i = 0; i < matrixSize; i++) {
        tabNodeValues[i][0] = matrix[i][0];
    }

    int bitMask = 0, newSubset = 0, counter = 0;
    bestPath[0] = 0;

    min = getMinimum(0, (int)(pow(2, matrixSize) - 2), matrix, tabNodeValues, possibleRouteTab,counter,bitMask,newSubset);
    counter = 1;

    findPath(0, int(pow(2, matrixSize) - 2), possibleRouteTab,bestPath,counter,bitMask,newSubset);

    bestPath[matrixSize] = bestPath[0];

    return min;
}