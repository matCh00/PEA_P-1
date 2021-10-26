#include "Menu.h"



Menu::Menu() {

}



Menu::~Menu() {

}



void Menu::startMenu() {

    // zmienne
    int key;
    int cities;
    bool run = true;
    string name;


    // argumenty modyfikowane przez algorytmy
    vector<int> path = {};
    int length = INT_MAX;


    // instancja grafu
    graph = new Graph();

    // instancja algorytmu BF
    bf = new BruteForce();

    // instancja algorytmu BB
    bb = new BranchAndBound();

    // instancja algorytmu DP
    dp = new DynamicProgramming();


    while (run) {

        cout << "\n [1] - wczytaj dane z pliku \n"
                " [2] - generuj losowy graf \n"
                " [3] - wyswietl graf \n"
                "  [4] - algorytm BF - przegladu zupelnego \n"
                "  [5] - algorytm BB - podzialu i ograniczen \n"
                "  [6] - algorytm DP - programowania dynamicznego \n"
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
                cout << "graf w postaci macierzy sasiedztwa: \n";
                graph->display();
                break;

            case 4:
                if (graph != nullptr) {

                    bf->algorithmBruteForce(graph, path, length);
                    cout << "\nkoszt: " << length << endl;
                    cout << "sciezka: ";
                    graph->displayPath(path);
                    cout << endl;
                    break;
                }
                else {

                    cout << "macierz jest pusta \n";
                }
                break;

            case 5:
                if (graph != nullptr) {

                    bb->algorithmBranchAndBound(graph, path, length);
                    cout << "\nkoszt: " << length << endl;
                    cout << "sciezka: ";
                    graph->displayPath(path);
                    cout << endl;
                    break;
                }
                else {

                    cout << "macierz jest pusta \n";
                }
                break;

            case 6:
                if (graph != nullptr) {

                    dp->algorithmDynamicProgramming(*&graph, path, length);
                    cout << "\nkoszt: " << length << endl;
                    cout << "sciezka: ";
                    graph->displayPath(path);
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
