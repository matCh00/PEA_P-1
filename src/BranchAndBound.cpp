#include "BranchAndBound.h"



BranchAndBound::BranchAndBound() {

    pathValue = 0;
    pathOfCities = {};
}



BranchAndBound::~BranchAndBound() {

    pathOfCities.clear();
}



int BranchAndBound::reduceGraph(int **distances) {}


int** BranchAndBound::markStep(int row, int col, int **distances) {}


void BranchAndBound::algorithmBranchAndBound(Graph graph, int source, vector<int> &finalPath, int &finalPathValue) {}