// plik reprezentujący graf

#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;



class Graph {

protected:

    // liczba miast
    int cities;

    // odległości pomiędzy miastami
    vector<vector<int>> distances;


public:

    // konstruktor
    Graph();

    // destruktor
    ~Graph();

    // wczytaj graf
    void loadFromfile(string fileName);

    // wyświetl graf
    void display();

};