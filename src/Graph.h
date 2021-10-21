// plik reprezentujący graf

#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;


// klasa reprezentująca graf
class Graph {

protected:

    // liczba miast
    int size;

    // odległości pomiędzy miastami [macierz]
    vector<vector<int>> matrix;


public:

    // konstruktor
    Graph();

    // destruktor
    ~Graph();

    // wczytaj graf z pliku
    void loadFromfile(string fileName);

    // wyświetl graf
    void display();

    // wyświetl ścieżkę
    void displayPath(vector<int> path);

    // liczba miast
    int getSize();

    // odległości pomiędzy miastami [macierz]
    vector<vector<int>> getMatrix();
};