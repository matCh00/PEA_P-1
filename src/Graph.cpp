#include "Graph.h"



Graph::Graph() {

    size = 0;
    matrix = nullptr;
}



Graph::~Graph() {

    // nie chcę niszczyć macierzy po każdym wykonanym algorytmie, bo kolejny będzie operował na tych samych danych
    // nie jest powiedziane że dla 100 powtórzeń algorytmu każde ma operować na innym zestawie danych

/*
    for (int i = 0; i < size; ++i)
        delete[] matrix[i];

    delete[] matrix;
*/
}



void Graph::loadFromfile(string fileName) {

    ifstream file;
    file.open(fileName);

    // sprawdzenie czy udało się otworzyć plik
    if (file.is_open()) {


        // wczytujemy liczbę miast
        file >> size;


        // rezerwujemy miejsce na dane
        matrix = new int*[size];
        for (int i = 0; i < size; ++i) {
            matrix[i] = new int[size];
        }


        // wypełniamy macierz początkową
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                matrix[i][j] = -1;
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


int** Graph::getMatrix() {

    return matrix;
}