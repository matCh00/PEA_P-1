#include "Menu.h"



Menu::Menu() {

}



Menu::~Menu() {

}



void Menu::start() {

    // zmienne
    int key = 0;
    bool run = true;
    string name = "";


    // testowy graf
    Graph *graph = new Graph();

    // testowy algorytm BF
    BruteForce *bruteForce = new BruteForce();


    while (run) {

        cout << "\n [1] - wczytaj dane \n"
                " [2] - wyswietl graf \n"
                " [3] - algorytm BF - przegladu zupelnego \n"
                " [4] - algorytm BB - podzialu i ograniczen \n"
                " [5] - algorytm DP - programowania dynamicznego \n"
                " [9] - badanie efektywnosci \n"
                " [0] - wyjscie \n";

        cin >> key;
        cout << endl;

        switch (key) {

            case 1:
                cout << "podaj nazwe pliku: ";
                cin >> name;
                graph->loadFromfile(name);
                break;

            case 2:
                graph->display();
                break;

            case 3:
                cout << "minimalna sciezka (Brute Force): " << bruteForce->algorithmBruteForce(*graph, 0);
                break;

            case 4:
                break;

            case 5:
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
