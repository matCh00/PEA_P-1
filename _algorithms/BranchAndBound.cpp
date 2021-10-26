#include "BranchAndBound.h"



BranchAndBound::BranchAndBound() {

    cost = INT_MAX;
    path = {};
}



BranchAndBound::~BranchAndBound() {

    path.clear();
    visited.clear();
    curr_path.clear();
}

// TODO opisać działanie algorytmu

// Function to find the minimum edge cost
// having an end at the vertex i
int BranchAndBound::firstMin(Graph *graph, int i)
{
    int min = INT_MAX;
    for (int k=0; k < graph->getSize(); k++)
        if (graph->getCell(i, k)<min && i != k)
            min = graph->getCell(i, k);
        return min;
}

// function to find the second minimum edge cost
// having an end at the vertex i
int BranchAndBound::secondMin(Graph *graph, int i)
{
    int first = INT_MAX, second = INT_MAX;
    for (int j=0; j < graph->getSize(); j++)
    {
        if (i == j)
            continue;

        if (graph->getCell(i, j) <= first)
        {
            second = first;
            first = graph->getCell(i,j);
        }
        else if (graph->getCell(i, j) <= second &&
        graph->getCell(i, j) != first)
            second = graph->getCell(i, j);
    }
    return second;
}


void BranchAndBound::findPath(Graph *graph, int curr_bound, int curr_weight, int level, vector<int> curr_path) {

    int size = graph->getSize();
    // base case is when we have reached level N which
    // means we have covered all the nodes once
    if (level == size)
    {
        // check if there is an edge from last vertex in
        // path back to the first vertex
        if (graph->getCell(curr_path[level-1], curr_path[0]) != 0)
        {
            // curr_res has the total weight of the
            // solution we got
            int curr_res = curr_weight + graph->getCell(curr_path[level-1], curr_path[0]);

            // Update final result and final path if
            // current result is better.
            if (curr_res < cost)
            {
                path.clear();

                for (int i = 0; i < size; i++)
                    path.push_back(curr_path[i]);
                path.push_back(curr_path[0]);
                cost = curr_res;
            }
        }
        return;
    }

    // for any other level iterate for all vertices to
    // build the search space tree recursively
    for (int i = 0; i < size; i++)
    {
        // Consider next vertex if it is not same (diagonal
        // entry in adjacency matrix and not visited
        // already)
        if (graph->getCell(curr_path[level-1], i) != 0 && visited[i] == false)
        {
            int temp = curr_bound;
            curr_weight += graph->getCell(curr_path[level-1], i);

            // different computation of curr_bound for
            // level 2 from the other levels
            if (level==1)
                curr_bound -= ((firstMin(graph, curr_path[level-1]) +
                        firstMin(graph, i))/2);
            else
                curr_bound -= ((secondMin(graph, curr_path[level-1]) +
                        firstMin(graph, i))/2);

            // curr_bound + curr_weight is the actual lower bound
            // for the node that we have arrived on
            // If current lower bound < final_res, we need to explore
            // the node further
            if (curr_bound + curr_weight < cost)
            {
                curr_path[level] = i;
                visited[i] = true;

                // call findPath for the next level
                findPath(graph, curr_bound, curr_weight, level+1, curr_path);
            }

            // Else we have to prune the node by resetting
            // all changes to curr_weight and curr_bound
            curr_weight -= graph->getCell(curr_path[level-1], i);
            curr_bound = temp;

            // Also reset the visited array
            for (int j = 0; j < size; ++j) {
                visited[j] = false;
            }
            for (int j = 0; j <= level-1; j++)
                visited[curr_path[j]] = true;
        }
    }
}

void BranchAndBound::algorithmBranchAndBound(Graph* graph, vector<int>& finalPath, int& finalPathValue)
{
    int size = graph->getSize();

    path.reserve(size);
    visited.reserve(size);
    curr_path.reserve(size + 1);

    for (int i = 0; i < size; ++i) {
        visited.push_back(0);
    }

    for (int i = 0; i < size + 1; ++i)
    {
        curr_path.push_back(-1);
    }

    // Calculate initial lower bound for the root node
    // using the formula 1/2 * (sum of first min +
    // second min) for all edges.
    // Also initialize the curr_path and visited array
    int curr_bound = 0;

    // Compute initial bound
    for (int i = 0; i < size; i++)
        curr_bound += (firstMin(graph, i) + secondMin(graph, i));

    // Rounding off the lower bound to an integer
    curr_bound = (curr_bound&1)? curr_bound/2 + 1 : curr_bound/2;

    // We start at vertex 1 so the first vertex
    // in curr_path[] is 0
    visited[0] = true;
    curr_path[0] = 0;

    // Call to findPath for curr_weight equal to
    // 0 and level 1
    findPath(graph, curr_bound, 0, 1, curr_path);




    // zwrócenie ścieżki jako argumentu funkcji
    finalPath = path;

    // zwrócenie długości ścieżki jako argumentu funkcji
    finalPathValue = cost;
}



