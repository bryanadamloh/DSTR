#include <iostream>

using namespace std;

struct node {
	int data;
	struct node *next;
};

class SM {
	int rowP; 
	int columnP;

public:
	SM(int rows, int columns);
	~SM();
	void readElements();
	void printMatrix();
	SM *addSM();
};

SM::SM(int n, int m)
{

}

void SM::readElements()
{
	
}

void SM::printMatrix()
{

}