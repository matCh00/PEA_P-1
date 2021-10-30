#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <string>
#include <istream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdio>
#include <ctime>
#include <cstdlib>

using namespace std;

class Node {
public:
	//Default constructor
	Node();

	//Overload constructor
	Node(int, int, int, int, int**, int, int*);
	Node(int*, int*, int, int, int, int*);

	//Destructor
	~Node();

	//Accessor Function
	void copyMatrix(int**);
	void loadInfo();
	void setId(int );
	int getStartSize();
	string getInstanceName();
	int **getMatrix();
	int getIndex();
	int getId();
	int getSize();
	int getValue();
	int getLvl();
	int *getRoute();
	int *getVisited();
	int *getBeforeVisited();
	void generateRandMatrix();
	void setIndex(int);


private:
	//Member variables
	int size;
	int index;
	int id;
	int *beforeVisited;
	int *route;
	int *visited;
	int value;
	int lvl;
	int **matrix;
	int startMatrixSize;
	int **startMatrix;
	string instanceName;
};
#endif