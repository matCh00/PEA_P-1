#include "BranchAndBound.h"



BranchAndBound::BranchAndBound() {

}



BranchAndBound::~BranchAndBound() {

}



int BranchAndBound::branchAndBound(vector<vector<int>> matrix) {

    if (currSize <= 2) {

        // zwrócenie dolnego ograniczenia / kosztu
        return lowerBound;
    }

    // wyzerowanie dolnego ograniczenia
    lowerBound = 0;
    
    // dla każdego wiersza
    for (int i = 0; i < currSize; ++i) {

        int currMin = INT_MAX;

        // sprawdzenie każdego elementu
        for (int j = 0; j < currSize; ++j) {

            // znalezienie minimum
            if (matrix[i][j] < currMin && matrix[i][j] != 0 && matrix[i][j] != -1) {

                currMin = matrix[i][j];
            }
        }

        // odjęcie odnalezionego minimum od każdego elementu
        for (int j = 0; j < currSize; ++j) {

            matrix[i][j] -= currMin;
        }

        // jeżeli nie odnaleziono minimum
        if (currMin == INT_MAX) {

            currMin = 0;
        }

        // dolne ograniczenie to suma wszystkich minimum
        lowerBound += currMin;
    }

    // dla każdej kolumny
    for (int i = 0; i < currSize; ++i) {

        int currMin = INT_MAX;

        // sprawdzenie każdego elementu
        for (int j = 0; j < currSize; ++j) {

            // znalezienie minimum
            if (matrix[j][i] < currMin && matrix[j][i] != 0 && matrix[j][i] != -1) {

                currMin = matrix[j][i];
            }
        }

        // odjęcie odnalezionego minimum od każdego elementu
        for (int j = 0; j < currSize; ++j) {

            matrix[j][i] -= currMin;
        }

        // jeżeli nie odnaleziono minimum
        if (currMin == INT_MAX) {

            currMin = 0;
        }

        // dolne ograniczenie to suma wszystkich minimum
        lowerBound += currMin;
    }


    // największe minimum
    int maxMin = 0;

    // dla każdego wiersza
    for (int i = 0; i < currSize; ++i) {

        int currMin = INT_MAX;

        // licznik zer w wierszu
        int zeroCount = 0;

        // sprawdzenie każdego elementu
        for (int j = 0; j < currSize; ++j) {

            // znalezienie minimum
            if (matrix[i][j] < currMin && matrix[i][j] != -1 && (matrix[i][j] != 0 || zeroCount > 0)) {

                currMin = matrix[i][j];
            }

            // natrafiono na 0
            if (matrix[i][j] == 0) {

                zeroCount++;
            }
        }
        zeroCount = 0;

        // szukanie największego minimum
        if (maxMin < currMin) {

            maxMin = currMin;
        }
    }

    // dla każdej kolumny
    for (int i = 0; i < currSize; ++i) {

        int currMin = INT_MAX;

        // licznik zer w wierszu
        int zeroCount = 0;

        // sprawdzenie każdego elementu
        for (int j = 0; j < currSize; ++j) {

            // znalezienie minimum
            if (matrix[j][i] < currMin && matrix[j][i] != -1 && (matrix[j][i] != 0 || zeroCount > 0)) {

                currMin = matrix[j][i];
            }

            // natrafiono na 0
            if (matrix[j][i] == 0) {

                zeroCount++;
            }
        }
        zeroCount = 0;

        // szukanie największego minimum
        if (maxMin < currMin) {

            maxMin = currMin;
        }
    }


    // redukowanie macierzy dopóki rozmiar jej jest większy od 2
    // [skracanie w zależności od wystąpienia największego minimum:
    //   kolumnę] i dodatkowo wiersz gdy w skracanej kolumnie wystąpiło 0
    //   wiersz] i dodatkowo kolumnę gdy w skracanym wierszu wystąpiło 0

    bool alreadyReduced = false;
    bool foundMaxMinInColumn = false;

    // przeszukiwanie kolumn
    for (int i = 0; i < currSize; ++i) {

        for (int j = 0; j < currSize; ++j) {

            // znaleziono maxMin w kolumnie o indeksie i
            if (matrix[j][i] == maxMin) {

                foundMaxMinInColumn = true;
            }

            // jeżeli w kolumnie wystąpiło 0 oraz maxMin
            if (matrix[j][i] == 0 && foundMaxMinInColumn) {

                // j - indeks wiersza do redukcji
                // i - indeks kolumny do redukcji

                // zablokowanie przejścia powrotnego
                matrix[i][j] = INT_MAX;


                //REDUKCJA
                reduceMatrix(matrix, j, i);

                path.push_back(j);
                path.push_back(i);

                currSize--;

                // powiększenie dolnego ograniczenia o maxMin
                lowerBound += maxMin;

                alreadyReduced = true;
            }
        }
        foundMaxMinInColumn = false;
    }


    // jeżeli jeszcze nie nastąpiła redukcja
    if (alreadyReduced == false) {

        bool foundMaxMinInRow = false;

        // przeszukiwanie wierszy
        for (int i = 0; i < currSize; ++i) {

            for (int j = 0; j < currSize; ++j) {

                // znaleziono maxMin w wierszu o indeksie i
                if (matrix[i][j] == maxMin) {

                    foundMaxMinInRow = true;
                }

                // jeżeli w wierszu wystąpiło 0 oraz maxMin
                if (matrix[i][j] == 0 && foundMaxMinInRow) {

                    // i - indeks kolumny do redukcji
                    // j - indeks wiersza do redukcji

                    // zablokowanie przejścia powrotnego
                    matrix[j][i] = INT_MAX;


                    // REDUKCJA
                    reduceMatrix(matrix, j, i);

                    path.push_back(j);
                    path.push_back(i);

                    currSize--;

                    // powiększenie dolnego ograniczenia o maxMin
                    lowerBound += maxMin;
                }
            }
            foundMaxMinInRow = false;
        }
    }

    // wykonujemy kolejny raz
    cost = branchAndBound(matrix);
}



void BranchAndBound::reduceMatrix(vector<vector<int>> tempMatrix, int row, int column) {

    // usunięcie wiersza
    tempMatrix.erase(tempMatrix.begin() + row);

    // usunięcie kolumny
    for (size_t i = 0; i < tempMatrix.size(); ++i) {
        tempMatrix[i].erase(tempMatrix[i].begin() + column);
    }
}



void BranchAndBound::algorithmBranchAndBound(Graph* graph, vector<int>& finalPath, int& finalPathValue) {

    // przypisanie rozmiaru
    size = graph->getSize();
    currSize = size;

    cost = INT_MAX;

    // rezerwowanie miejsca
    path.reserve(size);

    // skopiowanie macierzy
    tempMatrix = graph->getMatrix();

    branchAndBound(tempMatrix);


    finalPathValue = cost;
    finalPath = path;

    tempMatrix.clear();
    path.clear();
}



