#include "BranchAndBound.h"



BranchAndBound::BranchAndBound() {

}



BranchAndBound::~BranchAndBound() {

}



void BranchAndBound::branchAndBound(vector<vector<int>> matrix) {

}



void BranchAndBound::reduceMatrix(vector<vector<int>> tempMatrix, int maximum) {

}



void BranchAndBound::algorithmBranchAndBound(Graph* graph, vector<int>& finalPath, int& finalPathValue) {

    // przypisanie rozmiaru
    size = graph->getSize();

    // rezerwowanie miejsca
    path.reserve(size);

    // skopiowanie macierzy
    tempMatrix = graph->getMatrix();

}



