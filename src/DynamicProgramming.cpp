#include "DynamicProgramming.h"



DynamicProgramming::DynamicProgramming() {

    cost = 0;
    path = {};
}



DynamicProgramming::~DynamicProgramming() {

    path.clear();
}



int DynamicProgramming::recursionTSP(Graph* graph, int visitedCities, int currentPos) {

    if(visitedCities == visitedAll) {
        shortestPath[visitedCities][currentPos] = to_string(currentPos);
        return graph->getCell(currentPos, 0);
    }
    if(savedPaths[visitedCities][currentPos]!=-1){
        return savedPaths[visitedCities][currentPos];
    }

    int ans = INT_MAX;
    string currentPath = "";

    for(int city=0; city<graph->getSize(); city++) {
        if((visitedCities&(1<<city)) == 0) {
            int newAns = graph->getCell(currentPos, city) + recursionTSP(graph, visitedCities|(1<<city), city);
            if((newAns < ans)) {
                ans = newAns;
                currentPath = to_string(currentPos) + "->" + shortestPath[visitedCities|(1<<city)][city];
            }
        }
    }
    shortestPath[visitedCities][currentPos] = currentPath;
    savedPaths[visitedCities][currentPos] = ans;
    return ans;
}



void DynamicProgramming::algorithmDynamicProgramming(Graph* graph, vector<int> &finalPath, int &finalCost) {

    int size = graph->getSize();
    visitedAll = (1<<size) - 1;
    savedPaths.reserve(1<<size);
    shortestPath.reserve(1<<size);

    for(int i=0;i<(1<<size);i++){
        vector<int> row;
        for(int j=0;j<size;j++){
            row.push_back(-1);
        }
        savedPaths.push_back(row);
    }

    for(int i=0;i<(1<<size);i++){
        vector<string> row;
        for(int j=0;j<size;j++){
            row.emplace_back("");
        }
        shortestPath.push_back(row);
    }

    recursionTSP(graph, 1, 0);
    cout << "DP:" << endl;
    cout << "shortest path: " << savedPaths[1][0] << endl;
    cout << shortestPath[1][0] << "->0" << endl;

    finalCost = savedPaths[1][0];

    for (int i = 0; i < shortestPath[1][0].size(); ++i) {
        finalPath.push_back(shortestPath[1][0][i]);
    }

    // zwolnienie pamięci
    savedPaths.clear();
    shortestPath.clear();
}