#include "Graph.h"



Graph::Graph() {

    size = 0;
}



Graph::~Graph() {

    matrix.clear();
}



void Graph::loadFromfile(string fileName) {

    ifstream file;
    file.open(fileName);

    // sprawdzenie czy udało się otworzyć plik
    if (file.is_open()) {


        // wczytujemy liczbę miast
        file >> size;

        matrix.resize(size);
        for (int i = 0; i < size; ++i) {
            matrix[i].resize(size);
        }

        // wypełniamy macierz początkową
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                matrix[i][j] = 0;
            }
        }


        // czytamy aż do końca pliku
        while (!file.eof()) {

            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    file >> matrix[i][j];
                }
            }
        }
    }
    else
        cout << "Nie mozna otworzyc pliku!";

    file.close();
}



void Graph::display() {

    cout << "graf w postaci macierzy sasiedztwa\n";

    for (int i = 0; i < size; ++i) {

        for (int j = 0; j < size; ++j) {

            cout << setw(5) << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}



void Graph::displayPath(vector<int> path) {

    for (size_t i = 0; i < path.size(); ++i) {

        if (i == path.size() - 1)
            cout << path[i];
        else
            cout << path[i] << " -> ";
    }
}



int Graph::getSize() {

    return size;
}


vector<vector<int>> Graph::getMatrix() {

    return matrix;
}