// algorytm programowania dynamicznego (algorytm Helda-Karpa)

#ifndef PEA_P_1_DYNAMICPROGRAMMING_H
#define PEA_P_1_DYNAMICPROGRAMMING_H

#include "../_structures/Graph.h"

using namespace std;


class DynamicProgramming {

private:

    // część algorytmu - znalezienie ścieźki
    void findPath(int start, int set, int size, vector<vector<int>>&possibleRouteTab,int*bestPath, int &c, int &bitMask, int &newSubset);

    // część algorytmu - znalezienie minimum
    int getMinimum(int firstNode, int set, int size, vector<vector<int>> matrix, vector<vector<int>>&tabNodeValues, vector<vector<int>>&possibleRouteTab, int &c, int &bitMask, int &newSubset);


public:

    // konstruktor
    DynamicProgramming();

    // destruktor
    ~DynamicProgramming();

    // algorytm główny
    int algorithmDynamicProgramming(vector<vector<int>> matrix, int* bestPath);
};


#endif
