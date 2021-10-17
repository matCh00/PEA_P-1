#include "Menu.h"



Menu::Menu() {

    // stworzenie grafu
    graph = new Graph();
}



Menu::~Menu() {

    system("cls");
}



void Menu::start() {

    int key = 0;
    bool run = true;
    string name = "";


    while (run) {

        cout << "\n [0] - wyjscie\n"
                " [1] - wczytaj dane\n"
                " [2] - wyswietl graf \n";

        cin >> key;
        cout << endl;

        switch (key) {

            case 0:
                run = false;
                break;

            case 1:
                cout << "podaj nazwe pliku: ";
                cin >> name;
                graph->loadFromfile(name);
                break;

            case 2:
                graph->display();
                break;

            default:
                break;

        }
    }
}
