#include "DynamicProgramming.h"
/*


DynamicProgramming::DynamicProgramming() {

    cost = 0;
    path = {};
}



DynamicProgramming::~DynamicProgramming() {

    path.clear();
}



void DynamicProgramming::algorithmDynamicProgramming(Graph graph, int source, vector<int> &finalPath, int &finalCost) {

    for (int i = 0; i < graph.getSize(); i++) {
        for (int j = 0; j < pow(2, graph.getSize()); j++)
            rememberPath[i][j] = 0;  ////////////////////////////////////
    }

    for (int i = 0; i < graph.getSize(); i++) {
        for (int j = 0; j < pow(2, graph.getSize()); j++)
            rememberDistance[i][j] = 0;
    }

    findMinTourCost(graph, source, 1);

    int j = 0;
    int position = 1;
    int currentVertex = 0;
    while (true) {
        path[j] = currentVertex;
        j++;
        int i = rememberPath[currentVertex][position];
        if (i == -1) break;
        int nextPosition = position | (1 << i);
        position = nextPosition;
        currentVertex = i;
    }
    path[j] = 0;

    std::cout << "\nPath: ";
    for (int i = 0; i < j; i++)
    {
        std::cout << path[i] << " -> ";
    }
    std::cout << path[j];
}



int DynamicProgramming::findMinTourCost(Graph graph, int currentVertex, int position) {

    int vertex;

    if (position == graph.getSize() - 1)
    {
        return graph.getMatrix()[currentVertex][0];
    }

    if (rememberDistance[currentVertex][position] != 0)
    {
        return rememberDistance[currentVertex][position];
    }

    int distance = INT32_MAX;

    for (int nextVertex = 0; nextVertex < graph.getSize(); nextVertex++)
    {
        if ((position&(1 << nextVertex)) != 0)
        {
            continue;
        }

        int nextPosition = position | (1 << nextVertex);

        int newDistance = graph.getMatrix()[currentVertex][nextVertex] + findMinTourCost(graph, nextVertex, nextPosition);

        if (newDistance < distance)
        {
            distance = newDistance;
            vertex = nextVertex;
        }
    }
    rememberPath[currentVertex][position] = vertex;
    return rememberDistance[currentVertex][position] = distance;
}

*/