#include "Graph.h"



Graph::Graph() {

}



Graph::~Graph() {

    //?? graf może znikać po jednym wykonaniu algorytmu
    matrix.clear();
}



Graph::Graph(int size) {

    Randomize r;

    // rezerwujemy pamięć
    matrix.reserve(size);

    for (int i = 0; i < size; i++) {
        vector<int> temp;
        temp.reserve(size);

        for (int j = 0; j < size; j++) {
            temp.push_back(r.random_mt19937(1, 99));
        }

        temp[i] = 0;
        this->matrix.push_back(temp);
    }

    // uzupełnianie przekątnej zerami
    for (int i = 0; i < size; i++) {

        matrix[i][i] = 0;
    }
}



Graph::Graph(Graph* graph) {

    // przypisujemy wskaźnik na aktualny graf
    this->matrix = graph->matrix;
}



Graph::Graph(string filePath) {

    ifstream file;
    file.open(filePath);

    string line;
    string item;

    // sprawdzamy czy udało się otworzyć plik
    if (file.is_open()) {

        // wczytujemy liczbę miast
        file >> size;

        // rezerwujemy miejsce
        matrix.reserve(size);

        // czytamy tylko tyle wierszy jaka jest wielkość macierzy
        for (int i = 0; i < size; ++i) {

            // rezerwowanie miejsca
            vector<int> row;
            row.reserve(size);

            // pobieramy linię
            getline(file, line);

            // strumień napisowy
            istringstream iss(line);

            // czytamy tylko tyle kolumn jaka jest wielkość macierzy
            for (int j = 0; j < size; ++j) {

                // pobieramy daną ze wcześniej wczytanej linii
                iss >> item;

                // sprawdzamy czy dana zawiera jedynie cyfry
                if (item.find_first_not_of( "0123456789" ) == false) {

                    cout << "W pliku znajduja sie znaki / litery";
                    exit(EXIT_FAILURE);
                }

                // umieszczamy daną
                row.push_back(stoi(item));
            }

            // umieszczamy wiersz w macierzy
            matrix.push_back(row);
        }

        file.close();
    }
    else {

        cout << "Nie mozna otworzyc pliku!";
        exit(EXIT_FAILURE);
    }
}



void Graph::display() {

    cout << "graf w postaci macierzy sasiedztwa\n";

    for (int i = 0; i < size; ++i) {

        for (int j = 0; j < size; ++j) {

            cout << setw(5) << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}



void Graph::displayPath(vector<int> path) {

    for (size_t i = 0; i < path.size(); ++i) {

        if (i == path.size() - 1)
            cout << path[i];
        else
            cout << path[i] << " -> ";
    }
}



void Graph::setCell(int x, int y, int value) {

    matrix[x][y] = value;
}



int Graph::getCell(int x, int y) {

    return matrix[x][y];
}



int Graph::getSize() {

    return size;
}



void Graph::copyMatrix(Graph* old) {

    this->matrix = old->matrix;
}




