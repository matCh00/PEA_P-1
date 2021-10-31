#include "Menu.h"



Menu::Menu() {

}



Menu::~Menu() {

}



void Menu::startMenu() {

    // do menu
    int key;
    bool run = true;
    string name;
    int cities;


    // instancja grafu
    graph = new Graph();


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

                    BruteForce *bf = new BruteForce();

                    int* path = new int[graph->getSize() + 1];
                    int cost;

                    cost = bf->algorithmBruteForce(graph->getMatrix(), path);

                    cout << "Koszt: " << cost << endl;
                    cout << "Sciezka: " ;
                    for (int i = 0; i < graph->getSize(); i++)
                        cout << path[i] << " -> ";
                    cout << path[graph->getSize()];

                    break;
                }
                else {

                    cout << "macierz jest pusta \n";
                }
                break;

            case 5:
                if (graph != nullptr) {

                    BranchAndBound *bb = new BranchAndBound();

                    int* path = new int[graph->getSize() + 1];
                    int cost;

                    cost = bb->algorithmBranchAndBound(graph->getMatrix(), path);

                    cout << "Koszt: " << cost << endl;
                    cout << "Sciezka: " ;
                    for (int i = 0; i < graph->getSize(); i++)
                        cout << path[i] << " -> ";
                    cout << path[graph->getSize()];

                    break;
                }
                else {

                    cout << "macierz jest pusta \n";
                }
                break;

            case 6:
                if (graph != nullptr) {

                    DynamicProgramming *dp = new DynamicProgramming();

                    int* path = new int[graph->getSize() + 1];
                    int cost;

                    cost = dp->algorithmDynamicProgramming(graph->getMatrix(), path);

                    cout << "Koszt: " << cost << endl;
                    cout << "Sciezka: " ;
                    for (int i = 0; i < graph->getSize(); i++)
                        cout << path[i] << " -> ";
                    cout << path[graph->getSize()];

                    break;
                }
                else {

                    cout << "macierz jest pusta \n";
                }
                break;

            case 9:

                system("PAUSE");
                Tests tests;
                //tests.startTests();
                tests.startAutomaticTests();
                break;

            case 0:
                run = false;
                break;

            default:
                break;

        }
    }
}