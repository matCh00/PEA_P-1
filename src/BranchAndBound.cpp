#include "BranchAndBound.h"



BranchAndBound::BranchAndBound() {

    cost = 0;
    path = {};
}



BranchAndBound::~BranchAndBound() {

    path.clear();
}




void BranchAndBound::algorithmBranchAndBound(Graph graph, int source, vector<int>& finalPath, int& finalPathValue)
{
    vector<BB> vector = {};	//tworze wektor do przechowywania wlasnych struktur
    BB firstReduction = matrixStartReduction(graph.getMatrix(), graph.getSize(), source);		//tworze strukture, w ktorej będę przechowywał pierwsza zredukowana macierz
    vector.push_back(firstReduction);	//dodaje do vektora "macierz pierwszej redukcji"
    BB temp = vector.front();	//tworze pomocnicza zmienną, w ktorej będę przechowywał chwilowo rozpatrywaną strukture
    int index = 0;		//tworze zmienna index, ktora bedzie przechowywac index "najlepszej" struktury z wektora
    bool loopOn = true;		//zmienna logiczna sprawdzajaca, czy znaleziono już ścieżkę
    do
    {
        vector.erase(vector.begin() + index);	//usuwam z wektora strukture, którą będę teraz rozpatrywał w pętli
        for (int i = 0; i < graph.getSize(); i++)	//iteruje po wszystkich wierzchołkach
            if (!temp.visited[i])		//sprawdzam, czy wierzcholek byl juz odwiedzony wczesniej
                {
                BB temp2 = reducing(graph, temp, temp.currentVertex, i, source);		//tworze druga zmienna pomocnicza i przetwarzam ją funkcją obliczającą redukcje
                vector.push_back(temp2);	//dodaje strukture do wektora
                }
        //-------ZNALEZIENIE NAJMNIEJSZEGO-------//
        int minRed = INT_MAX;	//ustawiam minimalna redukcje na nieskonczonosc
        index = NULL;		//zeruje index
        for (size_t i = 0; i < vector.size(); i++)		//iteruje po wszystkich wierzcholkach
            if (vector[i].temporaryCost < minRed)		//sprawdzam czy redukcja chwilowej struktury jest mniejsza niz aktualna najmniejsza
                {
                index = i;		//zapamietuje index tejze struktury w wektorze
                minRed = vector[i].temporaryCost;	//aktualizuje najmniejsza redukcję
                }
        //---------------------------------------//

        temp = vector[index];			//przypisuje zmiennej pomocniczej nową strukture, ktora znajduje sie w wektorze struktur pod indeksem "index"
        cost = temp.temporaryCost;		//aktualizuje chwilowy najmniejszy koszt
        path = temp.path;				//aktualizuje chwilową ścieżkę hamiltona, dla chwilowego kosztu
        loopOn = isVisitedLeft(temp.visited, graph.getSize());		//sprawdzam czy została już znaleziona ścieżka
    } while (loopOn);		//pętla dzizła dopóki nie zostanie znaleziona ścieżka

    path.push_back(source);	//dodaje do ścieżki ostatni wierzchołek, którym jest wierzchołek startowy
    do{
        for (int i = 0; i < graph.getSize(); i++)
            vector[0].currentGraph[i].clear();
        vector[0].currentGraph.clear();
        vector[0].visited.clear();
        vector.erase(vector.begin());
    } while (!vector.empty());




    // zwrócenie ścieżki jako argumentu funkcji
    finalPath = path;

    // zwrócenie długości ścieżki jako argumentu funkcji
    finalPathValue = cost;
}



BB BranchAndBound::matrixStartReduction(vector<vector<int>> graph, int verticles, int source)
{
    BB result;		//tworze obiekt struktury, ktory bedzie przechowywal wyniki
    result.currentGraph = copyGraph(graph, verticles);	//kopiuje podany graf, zeby moc potem na nim dokonac redukcji ---- zapisuje go rowniez od razu w strukturze

    result.temporaryCost = 0;		//zmienna przechowujaca wartosc redukcji podstawowej

    //--------------WIERSZE------------------//
    for (int i = 0; i < verticles; i++)		//przechodzenie po wszystkich wierszach
        {
        int minValue = SHRT_MAX;			//poczatkowa wartosc minimalna jest rowna maksymalnej wartosci "int int"
        for (int j = 0; j < verticles; j++)			//przechodzenie po wszystkich kolumnach
            if (i != j)			//mijanie przekatnej macierzy
                {
                if (result.currentGraph[i][j] == 0)		//jesli któraś komórka jest równa 0, to warunek spełniony, można zrezygnować z dalszego sprawdzania
                    {
                    minValue = 0;		//ustawienie minimalnej wartosci na 0
                    break;				//porzucenie dalszego sprawdzania
                    }
                minValue = min(minValue, result.currentGraph[i][j]);		//sprawdzanie, czy jest to wartosc mniejsza od aktualnej minimalnej i ewentualna zamiana
                }
        else
            result.currentGraph[i][j] = SHRT_MAX;			//ustawiam "nieskonczonosc" na przekatnej macierzy
            for (int j = 0; j < verticles; j++)		//przechodzenie po wrzystkich kolumnach
                if (i != j)			//mijanie przekatnej macierzy
                    if (minValue != SHRT_MAX)	//sprawdzam, czy minimalna wartosc ulegla jakiejkolwiek zmianie
                        if (result.currentGraph[i][j] != SHRT_MAX)		//sprawdzam, czy dana komórka nie była już wczesniej zmieniana na nieskonczonosc
                            result.currentGraph[i][j] -= minValue;	//zmniejszanie kazdej wartosci w wierszu o jego wartosc minimalną
                            if (minValue != SHRT_MAX)			//sprawdzam, czy minimalna wartosc ulegla jakiejkolwiek zmianie
                                result.temporaryCost += minValue;	//uaktualniam calkowita redukcje
        }
    //--------------WIERSZE------------------//


    //--------------KOLUMNY------------------//
    for (int i = 0; i < verticles; i++)		//iteracja po kolumnach
        {
        int minValue = SHRT_MAX;			//poczatkowa wartosc minimalna jest rowna maksymalnej wartosci "short int"
        for (int j = 0; j < verticles; j++)		//iteracja po wierszach
            if (i != j)				//mijanie przekatnej macierzy
                {
                if (result.currentGraph[j][i] == 0)		//jesli któraś komórka jest równa 0, to warunek spełniony, można zrezygnować z dalszego sprawdzania
                    {
                    minValue = 0;		//ustawienie minimalnej wartosci na 0
                    break;				//porzucenie dalszego sprawdzania
                    }
                minValue = min(minValue, result.currentGraph[j][i]);		//sprawdzanie, czy jest to wartosc mniejsza od aktualnej minimalnej i ewentualna zamiana
                }
        else
            result.currentGraph[i][j] = SHRT_MAX;		//ustawiam "nieskonczonosc" na przekatnej macierzy
            for (int j = 0; j < verticles; j++)		//przechodzenie po wrzystkich wierszach
                if (i != j)			//mijanie przekatnej macierzy
                    if (minValue != SHRT_MAX)		//sprawdzam, czy minimalna wartosc ulegla jakiejkolwiek zmianie
                        if (result.currentGraph[j][i] != SHRT_MAX)		//sprawdzam, czy dana komórka nie była już wczesniej zmieniana na nieskonczonosc
                            result.currentGraph[j][i] -= minValue;	//zmniejszanie kazdej wartosci w wierszu o jego wartosc minimalną
                            if (minValue != SHRT_MAX)		//sprawdzam, czy minimalna wartosc ulegla jakiejkolwiek zmianie
                                result.temporaryCost += minValue;	//uaktualniam calkowita redukcje
        }
    //--------------KOLUMNY------------------//

    //result.visited = new bool[verticles];	//tworze dynamiczna tablice z lista odwiedzonych wierzcholkow
    result.visited.resize(verticles);



    for (int i = 0; i < verticles; i++)
        result.visited[i] = false;			//ustawiam wszystkie wierzcholki jako nieodwiedzone
    result.visited[source] = true;		//ustawiam wierzcholek poczatkowy jako odwiedzony
    result.currentVertex = source;		//ustawiam numer wierzcholka w ktorym jestem
    result.path.push_back(source);		//wstawiam aktualny wierzcholek do przechowywanej drogi
    return result;		//zwracam strukture z wynikami
}



vector<vector<int>> BranchAndBound::copyGraph(vector<vector<int>> graph, int size)
{
    vector<vector<int>> newGraph;		//tworze nowy wskaznik na tablice wskaznikow

    newGraph.resize(size);
    for (int i = 0; i < size; ++i) {
        newGraph[i].resize(size);//////////////
    }

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            newGraph[i][j] = graph[i][j];

        return newGraph;
}

vector<bool> BranchAndBound::copyVisited(vector<bool> visited, int size)
{
    vector<bool> newVisited;

    newVisited.resize(size);
    for (int i = 0; i < size; i++)
        newVisited[i] = visited[i];
    return newVisited;
}




BB BranchAndBound::reducing(Graph graph, BB given, int source, int endVert, int firstVertex)
{
    BB result;		//tworze strukture z wynikami
    result.temporaryCost = 0;		//ustawiam redukcje na 0
    result.currentGraph = copyGraph(given.currentGraph, graph.getSize());			//kopiuje do wynikow graf wejsciowy, aby moc go modyfikowac
    result.visited = copyVisited(given.visited, graph.getSize());	//kopiuje liste odwiedzonych wierzcholkow
    result.visited[endVert] = true;		//ustawiam aktualny wierzcholek jako odwiedzony
    result.currentVertex = endVert;		//ustawiam numer wierzcholka jako aktualny wierzcholek
    result.path = given.path;			//kopiuje droge ze struktury wejsciowej
    result.path.push_back(endVert);		//dodaje do drogi aktualny wierzcholek

    for (int i = 0; i < graph.getSize(); i++)
    {
        result.currentGraph[source][i] = SHRT_MAX;		//ustawiam wartości w wierszu wierzcholka z ktorego przechodze na nieskonczonosc
        result.currentGraph[i][endVert] = SHRT_MAX;		//ustawiam wartosci w kolumnie wierzcholka do ktorego przechodze na nieskonczonosc
    }
    result.currentGraph[endVert][firstVertex] = SHRT_MAX;	//ustawiam nieskonczonosc w komorce odpowiadajacej przejsciu z (wierzcholka do ktorego przechodze) do (wierzcholka startowego)

    //--------------WIERSZE------------------//
    for (int i = 0; i < graph.getSize(); i++)		//przechodzenie po wszystkich wierszach
        {
        int minValue = INT_MAX;			//poczatkowa wartosc minimalna jest rowna maksymalnej wartosci "short int"
        for (int j = 0; j < graph.getSize(); j++)			//przechodzenie po wszystkich kolumnach
            if (i != j)			//mijanie przekatnej macierzy
                {
                if (result.currentGraph[i][j] == 0)		//jesli któraś komórka jest równa 0, to warunek spełniony, można zrezygnować z dalszego sprawdzania
                    {
                    minValue = 0;		//ustawienie minimalnej wartosci na 0
                    break;				//porzucenie dalszego sprawdzania
                    }
                minValue = min(minValue, result.currentGraph[i][j]);		//sprawdzanie, czy jest to wartosc mniejsza od aktualnej minimalnej i ewentualna zamiana
                }

        for (int j = 0; j < graph.getSize(); j++)		//przechodzenie po wrzystkich kolumnach
            if (i != j)			//mijanie przekatnej macierzy
                if(minValue != SHRT_MAX)		//sprawdzam czy minimalna waga ulegla zmianie
                    if(result.currentGraph[i][j] != SHRT_MAX)		//sprawdzam, czy komorka nie jest juz rowna nieskonczonosci
                        result.currentGraph[i][j] -= minValue;		//zmniejszanie kazdej wartosci w wierszu o jego wartosc minimalną
                        if(minValue != SHRT_MAX)	//sprawdzam czy minimalna waga ulegla zmianie
                            result.temporaryCost += minValue;		//uaktualniam chwilowa redukcje
        }
    //--------------WIERSZE------------------//


    //--------------KOLUMNY------------------//
    for (int i = 0; i < graph.getSize(); i++)		//iteracja po kolumnach
        {
        int minValue = INT_MAX;			//poczatkowa wartosc minimalna jest rowna maksymalnej wartosci "short int"
        for (int j = 0; j < graph.getSize(); j++)		//iteracja po wierszach
            {
            if (i != j)				//mijanie przekatnej macierzy
                {
                if (result.currentGraph[j][i] == 0)		//jesli któraś komórka jest równa 0, to warunek spełniony, można zrezygnować z dalszego sprawdzania
                    {
                    minValue = 0;		//ustawienie minimalnej wartosci na 0
                    break;				//porzucenie dalszego sprawdzania
                    }
                minValue = min(minValue, result.currentGraph[j][i]);		//sprawdzanie, czy jest to wartosc mniejsza od aktualnej minimalnej i ewentualna zamiana
                }
            }

        for (int j = 0; j < graph.getSize(); j++)		//przechodzenie po wrzystkich wierszach
            if (i != j)			//mijanie przekatnej macierzy
                if (minValue != SHRT_MAX)		//sprawdzam czy minimalna waga ulegla zmianie
                    if (result.currentGraph[j][i] != SHRT_MAX)		//sprawdzam czy wartosc komórki nie wynosi nieskonczonosc
                        result.currentGraph[j][i] -= minValue;		//zmniejszanie kazdej wartosci w wierszu o jego wartosc minimalną
                        if (minValue != SHRT_MAX)		//sprawdzam czy minimalna waga ulegla zmianie
                            result.temporaryCost += minValue;		//uaktualniam chwilowa redukcje
        }

    result.temporaryCost += given.temporaryCost;		//uaktualniam redukcje o redukcje struktury wejsciowej
    result.temporaryCost += (int)given.currentGraph[source][endVert];	//uaktualniam redukcje o redukcje przejscia pomiedzy wierzcholkami w strukturze wejsciowej

    return result;		//zwracam strukture z wynikami   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

bool BranchAndBound::isVisitedLeft(vector<bool> visited, int size)
{
    for (int i = 0; i < size; i++)
        if (visited[i] == false)
            return true;
        return false;
}