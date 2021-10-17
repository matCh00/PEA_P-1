#include "Graph.h"



Graph::Graph() {

    numberOfCities = 0;
}



Graph::~Graph() {

    for (int i = 0; i < distancesBetweenCities.size(); ++i)
        distancesBetweenCities[i].clear();

    distancesBetweenCities.clear();
}



void Graph::loadFromfile(string fileName) {

    ifstream file;
    file.open(fileName);

    // sprawdzenie czy udało się otworzyć plik
    if (file.is_open()) {


        // wczytujemy liczbę miast
        file >> numberOfCities;


        // rezerwujemy miejsce na dane
        distancesBetweenCities.resize(numberOfCities);
        for (int i = 0; i < numberOfCities; ++i) {
            distancesBetweenCities[i].resize(numberOfCities);
        }


        // wypełniamy macierz początkową
        for (int i = 0; i < numberOfCities; ++i) {
            for (int j = 0; j < numberOfCities; ++j) {
                distancesBetweenCities[i][j] = -1;
            }
        }


        // czytamy aż do końca pliku
        while (!file.eof()) {

            for (int i = 0; i < numberOfCities; ++i) {
                for (int j = 0; j < numberOfCities; ++j) {
                    file >> distancesBetweenCities[i][j];
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

    for (int i = 0; i < distancesBetweenCities.size(); ++i) {

        for (int j = 0; j < distancesBetweenCities[i].size(); ++j) {

            cout << setw(5) << distancesBetweenCities[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}