// plik reprezentujący graf

#ifndef PEA_P_1_GRAPH_H
#define PEA_P_1_GRAPH_H

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>
#include <sstream>

using namespace std;


class Graph {

private:

    // macierz
    vector<vector<int>> matrix;

    // wielkość macierzy
    int size;

public:

    // pusty konstruktor
    Graph();

    // destruktor
    ~Graph();

    // konstruktor który rezerwuje miejsce
    Graph(int size);

    // konstruktor który przypisuje wskaźnik na macierz
    Graph(Graph* matrix);

    // konstruktor który wczytuje dane z pliku
    Graph(string filePath);

    // wypisanie grafu w postaci macierzy sąsiedztwa
    void display();

    // wypisanie ścieżki z podanej tablicy węzłów
    void displayPath(vector<int> path);

    // ustawienie komórki
    void setCell(int x, int y, int value);

    // pobranie komórki
    int getCell(int x, int y);

    // pobranie wielkości macierzy
    int getSize();

    // skopiowanie macierzy
    void copyMatrix(Graph* matrix);
};


#endif