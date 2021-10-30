#include "DynamicProgramming.h"
using namespace std;



DynamicProgramming::DynamicProgramming() {

}



DynamicProgramming::~DynamicProgramming() {

}



int DynamicProgramming::getMinimum(int firstNode, int set, int size, vector<vector<int>> matrix, vector<vector<int>>&tabNodeValues, vector<vector<int>>&possibleRouteTab, int &c, int &bitMask, int &newSubset) {

    int min = INT_MAX, tempMin;
    c++;
    if (tabNodeValues[firstNode][set] != -1) {
        return tabNodeValues[firstNode][set];
    }
    else {
        for (int i= 0; i < size; i++) {
            bitMask = pow(2, size) - 1 - pow(2, i);
            newSubset = set & bitMask;
            if (newSubset != set) {
                tempMin = matrix[firstNode][i] + getMinimum(i, newSubset, size, matrix, tabNodeValues, possibleRouteTab,c,bitMask,newSubset);	// c(start,x) + g(x,S-{x}) = Cij + G(j, S-{j})
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



void DynamicProgramming::findPath(int start, int set, int size, vector<vector<int>>&possibleRouteTab,int*bestPath, int &c, int &bitMask, int &newSubset) {

    if (possibleRouteTab[start][set] == -1) {
        return;
    }
    int i = possibleRouteTab[start][set];
    bestPath[c] = i;
    c++;

    bitMask = pow(2, size) - 1 - pow(2, i);
    newSubset = set & bitMask;

    findPath(i, newSubset, size, possibleRouteTab,bestPath,c,bitMask,newSubset);
}



// TODO opisać działanie algorytmu
int DynamicProgramming::algorithmDynamicProgramming(vector<vector<int>> matrix, int* bestPath) {

    int min = INT_MAX;

    vector<vector<int>> tabNodeValues;
    vector<vector<int>> possibleRouteTab;

    tabNodeValues.resize(matrix.size());
    possibleRouteTab.resize(matrix.size());

    for (int i = 0; i < matrix.size(); i++) {

        tabNodeValues.resize(pow(2, matrix.size()));
        possibleRouteTab.resize(pow(2, matrix.size()));

        for (int j = 0; j < pow(2, matrix.size()); j++) {

            tabNodeValues[i].push_back(-1);
            possibleRouteTab[i].push_back(-1);
        }
    }

    for (int i = 0; i < matrix.size(); i++) {
        tabNodeValues[i][0] = matrix[i][0];
    }

    int bitMask = 0, newSubset = 0, counter = 0;
    bestPath[0] = 0;

    min = getMinimum(0, pow(2, matrix.size()) - 2, matrix.size(), matrix, tabNodeValues, possibleRouteTab,counter,bitMask,newSubset);
    counter = 1;

    findPath(0, pow(2, matrix.size()) - 2, matrix.size(), possibleRouteTab,bestPath,counter,bitMask,newSubset);

    bestPath[matrix.size()] = bestPath[0];

    return min;
}