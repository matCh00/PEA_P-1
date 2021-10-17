#include "Graph.h"



Graph::Graph() {

    cities = 0;
}



Graph::~Graph() {

    for (int i = 0; i < distances.size(); ++i)
        distances[i].clear();

    distances.clear();
}



void Graph::loadFromfile(string fileName) {

    ifstream file;
    file.open(fileName);

    // sprawdzenie czy udało się otworzyć plik
    if (file.is_open()) {


        // wczytujemy liczbę miast
        file >> cities;


        // rezerwujemy miejsce na dane
        distances.resize(cities);
        for (int i = 0; i < cities; ++i) {
            distances[i].resize(cities);
        }


        // wypełniamy macierz zerami
        for (int i = 0; i < cities; ++i) {
            for (int j = 0; j < cities; ++j) {
                distances[i][j] = 0;
            }
        }


        // czytamy aż do końca pliku
        while (!file.eof()) {

            for (int i = 0; i < cities; ++i) {
                for (int j = 0; j < cities; ++j) {
                    file >> distances[i][j];
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

    for (int i = 0; i < distances.size(); ++i) {

        for (int j = 0; j < distances[i].size(); ++j) {

            cout << setw(5) << distances[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}