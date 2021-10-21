#include "BranchAndBound.h"



BranchAndBound::BranchAndBound() {

    pathCost = 0;
    path = {};
}



BranchAndBound::~BranchAndBound() {

    path.clear();
}

void BranchAndBound::calculatingPath(Graph graph, int startVert, vector<int>& finalPath, int& finalPathValue)
{
    std::vector<BB> vector;	//tworze wektor do przechowywania wlasnych struktur
    BB firstReduction = matrixStartReduction(graph.getDistances(), graph.getCities(), startVert);		//tworze strukture, w ktorej będę przechowywał pierwsza zredukowana macierz
    vector.push_back(firstReduction);	//dodaje do vektora "macierz pierwszej redukcji"
    BB temp = vector.front();	//tworze pomocnicza zmienną, w ktorej będę przechowywał chwilowo rozpatrywaną strukture
    int index = 0;		//tworze zmienna index, ktora bedzie przechowywac index "najlepszej" struktury z wektora
    bool loopOn = true;		//zmienna logiczna sprawdzajaca, czy znaleziono już ścieżkę
    do
    {
        vector.erase(vector.begin() + index);	//usuwam z wektora strukture, którą będę teraz rozpatrywał w pętli
        for (int i = 0; i < graph.getCities(); i++)	//iteruje po wszystkich wierzchołkach
            if (!temp.visited[i])		//sprawdzam, czy wierzcholek byl juz odwiedzony wczesniej
                {
                BB temp2 = reducing(graph, temp, temp.vertexNumber, i, startVert);		//tworze druga zmienna pomocnicza i przetwarzam ją funkcją obliczającą redukcje
                vector.push_back(temp2);	//dodaje strukture do wektora
                }
        //-------ZNALEZIENIE NAJMNIEJSZEGO-------//
        int minRed = INT_MAX;	//ustawiam minimalna redukcje na nieskonczonosc
        index = NULL;		//zeruje index
        for (int i = 0; i < vector.size(); i++)		//iteruje po wszystkich wierzcholkach
            if (vector[i].reduction < minRed)		//sprawdzam czy redukcja chwilowej struktury jest mniejsza niz aktualna najmniejsza
                {
                index = i;		//zapamietuje index tejze struktury w wektorze
                minRed = vector[i].reduction;	//aktualizuje najmniejsza redukcję
                }
        //---------------------------------------//

        temp = vector[index];			//przypisuje zmiennej pomocniczej nową strukture, ktora znajduje sie w wektorze struktur pod indeksem "index"
        pathCost = temp.reduction;		//aktualizuje chwilowy najmniejszy koszt
        path = temp.path;				//aktualizuje chwilową ścieżkę hamiltona, dla chwilowego kosztu
        loopOn = isVisitedLeft(temp.visited, graph.getCities());		//sprawdzam czy została już znaleziona ścieżka
    } while (loopOn);		//pętla dzizła dopóki nie zostanie znaleziona ścieżka

    path.push_back(startVert);	//dodaje do ścieżki ostatni wierzchołek, którym jest wierzchołek startowy
    do{
        for (int i = 0; i < graph.getCities(); i++)
            delete[] vector[0].graph[i];
        delete[] vector[0].graph;
        delete vector[0].visited;
        vector.erase(vector.begin());
    } while (!vector.empty());




    // zwrócenie ścieżki jako argumentu funkcji
    finalPath = path;

    // zwrócenie długości ścieżki jako argumentu funkcji
    finalPathValue = pathCost;
}



BB BranchAndBound::matrixStartReduction(int** graph, int verticles, int startVert)
{
    BB result;		//tworze obiekt struktury, ktory bedzie przechowywal wyniki
    result.graph = copyGraph(graph, verticles);	//kopiuje podany graf, zeby moc potem na nim dokonac redukcji ---- zapisuje go rowniez od razu w strukturze

    result.reduction = 0;		//zmienna przechowujaca wartosc redukcji podstawowej

    //--------------WIERSZE------------------//
    for (int i = 0; i < verticles; i++)		//przechodzenie po wszystkich wierszach
        {
        int minValue = SHRT_MAX;			//poczatkowa wartosc minimalna jest rowna maksymalnej wartosci "int int"
        for (int j = 0; j < verticles; j++)			//przechodzenie po wszystkich kolumnach
            if (i != j)			//mijanie przekatnej macierzy
                {
                if (result.graph[i][j] == 0)		//jesli któraś komórka jest równa 0, to warunek spełniony, można zrezygnować z dalszego sprawdzania
                    {
                    minValue = 0;		//ustawienie minimalnej wartosci na 0
                    break;				//porzucenie dalszego sprawdzania
                    }
                minValue = std::min(minValue, result.graph[i][j]);		//sprawdzanie, czy jest to wartosc mniejsza od aktualnej minimalnej i ewentualna zamiana
                }
        else
            result.graph[i][j] = SHRT_MAX;			//ustawiam "nieskonczonosc" na przekatnej macierzy
            for (int j = 0; j < verticles; j++)		//przechodzenie po wrzystkich kolumnach
                if (i != j)			//mijanie przekatnej macierzy
                    if (minValue != SHRT_MAX)	//sprawdzam, czy minimalna wartosc ulegla jakiejkolwiek zmianie
                        if (result.graph[i][j] != SHRT_MAX)		//sprawdzam, czy dana komórka nie była już wczesniej zmieniana na nieskonczonosc
                            result.graph[i][j] -= minValue;	//zmniejszanie kazdej wartosci w wierszu o jego wartosc minimalną
                            if (minValue != SHRT_MAX)			//sprawdzam, czy minimalna wartosc ulegla jakiejkolwiek zmianie
                                result.reduction += minValue;	//uaktualniam calkowita redukcje
        }
    //--------------WIERSZE------------------//


    //--------------KOLUMNY------------------//
    for (int i = 0; i < verticles; i++)		//iteracja po kolumnach
        {
        int minValue = SHRT_MAX;			//poczatkowa wartosc minimalna jest rowna maksymalnej wartosci "short int"
        for (int j = 0; j < verticles; j++)		//iteracja po wierszach
            if (i != j)				//mijanie przekatnej macierzy
                {
                if (result.graph[j][i] == 0)		//jesli któraś komórka jest równa 0, to warunek spełniony, można zrezygnować z dalszego sprawdzania
                    {
                    minValue = 0;		//ustawienie minimalnej wartosci na 0
                    break;				//porzucenie dalszego sprawdzania
                    }
                minValue = std::min(minValue, result.graph[j][i]);		//sprawdzanie, czy jest to wartosc mniejsza od aktualnej minimalnej i ewentualna zamiana
                }
        else
            result.graph[i][j] = SHRT_MAX;		//ustawiam "nieskonczonosc" na przekatnej macierzy
            for (int j = 0; j < verticles; j++)		//przechodzenie po wrzystkich wierszach
                if (i != j)			//mijanie przekatnej macierzy
                    if (minValue != SHRT_MAX)		//sprawdzam, czy minimalna wartosc ulegla jakiejkolwiek zmianie
                        if (result.graph[j][i] != SHRT_MAX)		//sprawdzam, czy dana komórka nie była już wczesniej zmieniana na nieskonczonosc
                            result.graph[j][i] -= minValue;	//zmniejszanie kazdej wartosci w wierszu o jego wartosc minimalną
                            if (minValue != SHRT_MAX)		//sprawdzam, czy minimalna wartosc ulegla jakiejkolwiek zmianie
                                result.reduction += minValue;	//uaktualniam calkowita redukcje
        }
    //--------------KOLUMNY------------------//

    result.visited = new bool[verticles];	//tworze dynamiczna tablice z lista odwiedzonych wierzcholkow
    for (int i = 0; i < verticles; i++)
        result.visited[i] = false;			//ustawiam wszystkie wierzcholki jako nieodwiedzone
        result.visited[startVert] = true;		//ustawiam wierzcholek poczatkowy jako odwiedzony

        result.vertexNumber = startVert;		//ustawiam numer wierzcholka w ktorym jestem
        result.path.push_back(startVert);		//wstawiam aktualny wierzcholek do przechowywanej drogi
        return result;		//zwracam strukture z wynikami
}



int** BranchAndBound::copyGraph(int** graph, int size)
{
    int **newGraph = new int*[size];		//tworze nowy wskaznik na tablice wskaznikow
    for (int i = 0; i < size; i++)
        newGraph[i] = new int[size];		//w kazdym wierszu tworze nowa tablice dynamiczna

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                newGraph[i][j] = graph[i][j];

            return newGraph;
}

bool* BranchAndBound::copyVisited(bool* visited, int size)
{
    bool *newVisited = new bool[size];
    for (int i = 0; i < size; i++)
        newVisited[i] = visited[i];
    return newVisited;
}




BB BranchAndBound::reducing(Graph graph, BB given, int startVert, int endVert, int firstVertex)
{
    BB result;		//tworze strukture z wynikami
    result.reduction = 0;		//ustawiam redukcje na 0
    result.graph = copyGraph(given.graph, graph.getCities());			//kopiuje do wynikow graf wejsciowy, aby moc go modyfikowac
    result.visited = copyVisited(given.visited, graph.getCities());	//kopiuje liste odwiedzonych wierzcholkow
    result.visited[endVert] = true;		//ustawiam aktualny wierzcholek jako odwiedzony
    result.vertexNumber = endVert;		//ustawiam numer wierzcholka jako aktualny wierzcholek
    result.path = given.path;			//kopiuje droge ze struktury wejsciowej
    result.path.push_back(endVert);		//dodaje do drogi aktualny wierzcholek

    for (int i = 0; i < graph.getCities(); i++)
    {
        result.graph[startVert][i] = SHRT_MAX;		//ustawiam wartości w wierszu wierzcholka z ktorego przechodze na nieskonczonosc
        result.graph[i][endVert] = SHRT_MAX;		//ustawiam wartosci w kolumnie wierzcholka do ktorego przechodze na nieskonczonosc
    }
    result.graph[endVert][firstVertex] = SHRT_MAX;	//ustawiam nieskonczonosc w komorce odpowiadajacej przejsciu z (wierzcholka do ktorego przechodze) do (wierzcholka startowego)

    //--------------WIERSZE------------------//
    for (int i = 0; i < graph.getCities(); i++)		//przechodzenie po wszystkich wierszach
        {
        int minValue = INT_MAX;			//poczatkowa wartosc minimalna jest rowna maksymalnej wartosci "short int"
        for (int j = 0; j < graph.getCities(); j++)			//przechodzenie po wszystkich kolumnach
            if (i != j)			//mijanie przekatnej macierzy
                {
                if (result.graph[i][j] == 0)		//jesli któraś komórka jest równa 0, to warunek spełniony, można zrezygnować z dalszego sprawdzania
                    {
                    minValue = 0;		//ustawienie minimalnej wartosci na 0
                    break;				//porzucenie dalszego sprawdzania
                    }
                minValue = std::min(minValue, result.graph[i][j]);		//sprawdzanie, czy jest to wartosc mniejsza od aktualnej minimalnej i ewentualna zamiana
                }

        for (int j = 0; j < graph.getCities(); j++)		//przechodzenie po wrzystkich kolumnach
            if (i != j)			//mijanie przekatnej macierzy
                if(minValue != SHRT_MAX)		//sprawdzam czy minimalna waga ulegla zmianie
                    if(result.graph[i][j] != SHRT_MAX)		//sprawdzam, czy komorka nie jest juz rowna nieskonczonosci
                        result.graph[i][j] -= minValue;		//zmniejszanie kazdej wartosci w wierszu o jego wartosc minimalną
                        if(minValue != SHRT_MAX)	//sprawdzam czy minimalna waga ulegla zmianie
                            result.reduction += minValue;		//uaktualniam chwilowa redukcje
        }
    //--------------WIERSZE------------------//


    //--------------KOLUMNY------------------//
    for (int i = 0; i < graph.getCities(); i++)		//iteracja po kolumnach
        {
        int minValue = INT_MAX;			//poczatkowa wartosc minimalna jest rowna maksymalnej wartosci "short int"
        for (int j = 0; j < graph.getCities(); j++)		//iteracja po wierszach
            {
            if (i != j)				//mijanie przekatnej macierzy
                {
                if (result.graph[j][i] == 0)		//jesli któraś komórka jest równa 0, to warunek spełniony, można zrezygnować z dalszego sprawdzania
                    {
                    minValue = 0;		//ustawienie minimalnej wartosci na 0
                    break;				//porzucenie dalszego sprawdzania
                    }
                minValue = std::min(minValue, result.graph[j][i]);		//sprawdzanie, czy jest to wartosc mniejsza od aktualnej minimalnej i ewentualna zamiana
                }
            }

        for (int j = 0; j < graph.getCities(); j++)		//przechodzenie po wrzystkich wierszach
            if (i != j)			//mijanie przekatnej macierzy
                if (minValue != SHRT_MAX)		//sprawdzam czy minimalna waga ulegla zmianie
                    if (result.graph[j][i] != SHRT_MAX)		//sprawdzam czy wartosc komórki nie wynosi nieskonczonosc
                        result.graph[j][i] -= minValue;		//zmniejszanie kazdej wartosci w wierszu o jego wartosc minimalną
                        if (minValue != SHRT_MAX)		//sprawdzam czy minimalna waga ulegla zmianie
                            result.reduction += minValue;		//uaktualniam chwilowa redukcje
        }

    result.reduction += given.reduction;		//uaktualniam redukcje o redukcje struktury wejsciowej
    result.reduction += (int)given.graph[startVert][endVert];	//uaktualniam redukcje o redukcje przejscia pomiedzy wierzcholkami w strukturze wejsciowej

    return result;		//zwracam strukture z wynikami
}

bool BranchAndBound::isVisitedLeft(bool* visited, int size)
{
    for (int i = 0; i < size; i++)
        if (visited[i] == false)
            return true;
        return false;
}

std::vector<int> BranchAndBound::getPath()
{
    return path;
}