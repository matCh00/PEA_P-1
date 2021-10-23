#include "Menu.h"



Menu::Menu() {

}



Menu::~Menu() {

}



void Menu::startMenu() {

    // zmienne
    int key = 0;
    int cities;
    bool run = true;
    string name = "";


    // argumenty modyfikowane przez algorytmy
    //vector<int> path = {};
    //int length = 0;


    // instancja grafu
    Graph *graph = new Graph();

    // instancja algorytmu BF
    BruteForce *bf = new BruteForce();

    // instancja algorytmu BB
    BranchAndBound *bb = new BranchAndBound();

    // instancja algorytmu DP
    DynamicProgramming *dp = new DynamicProgramming();


    while (run) {

        cout << "\n [1] - wczytaj dane z pliku \n"
                " [2] - generuj losowy graf \n"
                " [3] - wyswietl graf \n"
                " [4] - algorytm BF - przegladu zupelnego \n"
                " [5] - algorytm BB - podzialu i ograniczen \n"
                " [6] - algorytm DP - programowania dynamicznego \n"
                " [9] - badanie efektywnosci \n"
                " [0] - wyjscie \n";

        cin >> key;
        cout << endl;

        switch (key) {

            case 1:
                cout << "podaj nazwe pliku: ";
                cin >> name;
                graph = new Graph(name);
                break;

            case 2:
                cout << "podaj ilosc miast: ";
                cin >> cities;
                graph = new Graph(cities);
                break;

            case 3:
                cout << "graf w mostaci macierzy sąsiedztwa: \n";
                graph->display();
                break;

            case 4:
                if (graph != nullptr) {

                    bf->findPermutations(graph);
                    cout << endl;
                    break;
                }
                else {

                    cout << "macierz jest pusta \n";
                }
                break;

            case 5:
                if (graph != nullptr) {

                    bb->run(graph);
                    cout << endl;
                    break;
                }
                else {

                    cout << "macierz jest pusta \n";
                }
                break;

            case 6:
                if (graph != nullptr) {

                    dp->run(graph);
                    cout << endl;
                    break;
                }
                else {

                    cout << "macierz jest pusta \n";
                }
                break;

            case 9:
                break;

            case 0:
                run = false;
                break;

            default:
                break;

        }
    }
}
