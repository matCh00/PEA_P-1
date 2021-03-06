#include "BranchAndBound.h"


BranchAndBound::BranchAndBound() {

}


BranchAndBound::~BranchAndBound() {

    delete[] path;
    delete[] possiblePath;
    visited.clear();
    thisMatrix.clear();
}


/*
 *  algorytm podziału i ograniczeń
 *  metoda opiera się na przeszukiwaniu drzewa reprezentującego przestrzen rozwiązań problemu
 *  odcięcia redukują liczbę przeszukiwanych wierzchołków przyspieszając rozwiązanie
 *  w danej metodzie rozgałęzienia tworzą następników danego wierzchołka
 *  a ograniczenia odcinają części drzewa, w których na pewno nie ma optymalnego rozwiązania
 *  jest to metoda Depth First - po wybraniu wierzchołka z najlepszym dolnym ograniczeniem schodzi wgłąb aż do liścia
 *  dając nowe dolne ograniczenia, które mogą zamienić górne ograniczenie
 */



int BranchAndBound::minimumLine(int line, int matrixSize) {

    int min = INT_MAX;

    // przeszukujemy cały wiersz
    for (int i = 0; i < matrixSize; i++) {

        // jeżeli znaleziono minimum i wierzchołek do którego prowadzi minimum nie został jeszcze odwiedzony
        if (thisMatrix[line][i] < min && line != i && visited[i] == false)

            // przypisujemy minimum
            min = thisMatrix[line][i];
    }

    return min;
}



void BranchAndBound::treeSearch(int lowerBound, int cost, int level, int matrixSize) {

    // gdy dotarliśmy do ostatniego poziomu (ZESZLIŚMY DO LIŚCIA)
    if (level == matrixSize) {

        // jeżeli istnieje połączenie
        if (thisMatrix[possiblePath[level - 1]][possiblePath[0]] != -1) {

            int result = cost + thisMatrix[possiblePath[level - 1]][possiblePath[0]];

            // znaleziono nowe optymalne rozwiązanie
            if (result < bestCost) {

                // przepisanie ścieżki
                for (int i = 0; i < matrixSize; i++)
                    path[i] = possiblePath[i];

                // dodanie pierwszego miasta na koniec
                path[matrixSize] = possiblePath[0];

                // optymalny koszt
                bestCost = result;
            }
        }
        return;
    }

// nie dotarliśmy do ostatniego poziomu

    for (int i = 0; i < matrixSize; i++) {

        // jeżeli istnieje połączenie i wierzchołek do którego prowadzi nie został jeszcze odwiedzony
        if (thisMatrix[possiblePath[level - 1]][i] != -1 && visited[i] == false) {

            // tymczasowe dolne ograniczenie (NOWE DOLNE OGRANICZENIE DLA NASTĘPNEGO POZIOMU)
            int tempBound = lowerBound;
            lowerBound = 0;

            // dodanie kosztu
            cost += thisMatrix[possiblePath[level - 1]][i];

            // dla wszystkich węzłow
            for (int j = 1; j < matrixSize; j++) {

                // resetowanie tablicy z odwiedzonymi wierzchołkami
                if (j == i)
                    visited[0] = true;
                else
                    visited[0] = false;

                // dodanie do dolnego ograniczenia minimów z lini (potomków których nie odwiedzono)
                if (visited[j] == false)
                    lowerBound += minimumLine(j, matrixSize);
            }

            visited[0] = true;

            // jeżeli znaleziono lokalne optymalne rozwiązanie
            if (lowerBound + cost < bestCost) {

                // dodanie wierzchołka do możliwej optymalnej ścieżki
                possiblePath[level] = i;
                visited[i] = true;

                // przeszukiwanie drzewa dla kolejnego poziomu (SCHODZENIE W GŁĄB AŻ DO LIŚCIA)
                treeSearch(lowerBound, cost, level + 1, matrixSize);
            }

            // redukcja kosztu
            cost -= thisMatrix[possiblePath[level - 1]][i];

            // przypisujemy zapamiętane wcześniej dolne ograniczenie
            lowerBound = tempBound;

            // reset tablicy z odwiedzonymi wierzchołkami
            fill(visited.begin(), visited.end(), false);

            // ustawienie odwiedzonych wierzchołków do aktualnego poziomu
            for (int j = 0; j <= level - 1; j++)
                visited[possiblePath[j]] = true;
        }
    }
}



int BranchAndBound::algorithmBranchAndBound(vector<vector<int>> matrix, int* bestPath) {

    // skopiowanie macierzy do lokalnej
    thisMatrix.insert(thisMatrix.end(), matrix.begin(), matrix.end());

    // wartości początkowe
    int matrixSize = matrix.size();

    // górne ograniczenie - optymalny koszt
    bestCost = INT_MAX;

    // dolne ograniczenie
    int lowerBound = 0;

    // rezerwacja miejsca
    possiblePath = new int[matrixSize + 1];
    path = new int[matrixSize + 1];
    visited.resize(matrixSize);

    // początkowe wartości
    fill(visited.begin(), visited.end(), false);


    // obliczanie dolnej granicy
    for (int i = 0; i < matrixSize; i++)
        lowerBound += minimumLine(i, matrixSize);

    visited[0] = true;
    possiblePath[0] = 0;

    // przeszukujemy drzewo od korzenia
    treeSearch(lowerBound, 0, 1, matrixSize);


    // przypisujemy optymalną ścieżkę
    for (int i = 0; i < matrixSize + 1; ++i)
        bestPath[i] = path[i];

    // zwracamy optymalny koszt
    return bestCost;
}

