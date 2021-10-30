// algorytm podziału i ograniczeń

#ifndef PEA_P_1_BRANCHANDBOUND_H
#define PEA_P_1_BRANCHANDBOUND_H

#include "../_structures/Graph.h"
#include "../_structures/Node.h"

using namespace std;



class BranchAndBound {
public:
    int getFirstUpperBound(int *bestTab, int size, int&helpMin, int **macierz, int **mainMacierz, int *visitedTab, int &tempMin, int *routeTab, int &savedBestCol, int &nodesAmount, vector<Node>& graph, int &deleteNodesAmount);
    int graphTidying(vector<Node>& graph, int &tempLevel, int&deleteNodesAmount, int min, int &index);
    void prepareNextIteration(int &helpMin, vector<Node>& graph, int size, int *visitedTab, int *routeTab, int index, int **macierz, int **mainMacierz, int &tempLevel, int&counter, int &deleteNodesAmount);
    void developingGraph(int min, int tempLevel, int size, bool &ifBetter, int &bestMin, int *visitedTab, int **macierz, int **mainMacierz, int *routeTab, int savedBestCol, int &tempMin, int &helpMin, int counter, vector<Node>& graph, int &nodesAmount, int &deleteNodesAmount);
    int BBMain(Node start, int *bestTab);
    void suitableRowColToInf(int **matrix, int row, int col, int size);
    int reduceMatrix(int **matrix, int size);

    BranchAndBound();
    ~BranchAndBound();
};

#endif

