#include "BranchAndBound.h"
/*


BranchAndBound::BranchAndBound() {

}



BranchAndBound::~BranchAndBound() {

}

// TODO opisać działanie algorytmu
// TODO czasami źle liczy

// szukanie minimalnego kosztu dla poziomu 1
int BranchAndBound::firstMin(Graph *graph, int i)
{
    int min = INT_MAX;
    for (int k=0; k < graph->getSize(); k++)
        if (graph->getCell(i, k)<min && i != k)
            min = graph->getCell(i, k);
        return min;
}

// szukanie minimalnego kosztu dla wyższych poziomów
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
        else if (graph->getCell(i, j) <= second && graph->getCell(i, j) != first)
            second = graph->getCell(i, j);
    }
    return second;
}


void BranchAndBound::findPath(Graph *graph, int currBound, int currWeight, int level, vector<int> currPath) {

    int size = graph->getSize();

    // jeżeli wszystkie węzły zostały odwiedzone raz
    if (level == size)
    {
        // jeżeli jest połączenie pomiędzy ostatnim a pierwszym wierzchołkiem
        if (graph->getCell(currPath[level-1], currPath[0]) != 0)
        {
            // aktualizacja aktualnie optymalnego kosztu
            int currCost = currWeight + graph->getCell(currPath[level-1], currPath[0]);

            // aktualizacja rozwiązania o połączenie pomiędzy ostatnim a pierwszym węzłem
            if (currCost < cost)
            {
                path.clear();

                // skopiowanie ścieżki
                path = currPath;

                // dodanie pierwszego elementu na koniec
                path.push_back(currPath[0]);

                // przypisanie kosztu
                cost = currCost;
            }
        }
        return;
    }

    // iteracja dla innych poziomów - rekurencyjne budowanie drzewa wyszukiwania
    for (int i = 0; i < size; i++)
    {

        // rozważanie kolejnego wierzchołka jeżeli nie jest odwiedzony i nie jest przekątną
        if (graph->getCell(currPath[level-1], i) != 0 && visited[i] == false)
        {
            int temp = currBound;

            // aktualizacja kosztu
            currWeight += graph->getCell(currPath[level-1], i);

            // inaczej oblicza się granicę dla pierwszego poziomu niż dla wyższych poziomów
            if (level==1)
                currBound -= ((firstMin(graph, currPath[level-1]) + firstMin(graph, i))/2);
            else
                currBound -= ((secondMin(graph, currPath[level-1]) + firstMin(graph, i))/2);

            // jeżeli aktualna dolna granica dla badanego węzła jest mniejsza od aktualnego kosztu ścieżki
            if (currBound + currWeight < cost)
            {
                currPath[level] = i;
                visited[i] = true;

                // szukanie ścieżki dla kolejnego poziomu
                findPath(graph, currBound, currWeight, level+1, currPath);
            }

            // przycięcie węzła - resetowanie zmian
            currWeight -= graph->getCell(currPath[level-1], i);
            currBound = temp;

            // resetowanie tablicy
            for (int j = 0; j < size; ++j) {
                visited[j] = false;
            }

            // ustawienie wartości zgodnie z aktualną ścieżką
            for (int j = 0; j <= level-1; j++)
                visited[currPath[j]] = true;
        }
    }
}

void BranchAndBound::algorithmBranchAndBound(Graph* graph, vector<int>& finalPath, int& finalPathValue)
{
    int size = graph->getSize();

    // wartości początkowe
    cost = INT_MAX;

    // rezerwacja miejsca w wektorach
    path.reserve(size + 1);
    visited.reserve(size);
    currPath.reserve(size + 1);

    // początkowe wartości
    for (int i = 0; i < size; ++i) {
        visited.push_back(false);
        currPath.push_back(-1);
    }

    // początkowa dolna granica dla początkowego miasta
    int currBound = 0;

    // obliczenie początkowej granicy
    for (int i = 0; i < size; i++)
        currBound += (firstMin(graph, i) + secondMin(graph, i));

    // zaokrąglenie dolnego ograniczenia
    currBound = (currBound&1)? currBound/2 + 1 : currBound/2;

    // zaczynamy od początku, pierwsze miasto jest odwiedzone
    visited[0] = true;
    currPath[0] = 0;

    // wyszukanie ścieżki, zaczynamy z kosztem 0 i poziomem 1
    findPath(graph, currBound, 0, 1, currPath);


    // zwrócenie kosztu oraz ścieżki
    finalPath = path;
    finalPathValue = cost;


    // zwolnienie pamięci
    path.clear();
    visited.clear();
    currPath.clear();
}

*/

