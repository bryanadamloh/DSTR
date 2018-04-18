#include <iostream>

using namespace std;

struct column
{
	int columnIndex;
	int value;
	column *next;
};

struct row
{
	int rowIndex;
	row *next;
	column *first;
};

class SM {
	int rowPos, columnPos;
	row *first = NULL, *list = NULL;

public:
	int totalRow, totalCol;
	SM();
	SM(int rows, int columns);
	~SM();
	void readElements();
	void printMatrix();
};

SM::SM(int rows, int columns)
{
	int i;
	totalRow = rows;
	totalCol = columns;
}

SM::SM()
{

}

SM::~SM()
{

}

void SM::readElements()
{
	
}

void SM::printMatrix()
{

}

int main()
{
	int row, column;

	cout << "Sparse Matrix using Linked List\n";
	cout << "Enter the number of rows of the matrix:\n";
	cin >> row;
	cout << "Enter the number of columns of the matrix:\n";
	cin >> column;

	SM a(row, column);

	cout << "Sparse Matrix has been created!\n";

	mainMenu();
}

int mainMenu()
{
	SM s;
	int choice;

	while (1)
	{
		cout << "-----------------------------------\n";
		cout << "  Sparse Matrix using Linked List  \n";
		cout << "-----------------------------------\n";
		cout << "1. Add new elements into the matrix\n";
		cout << "2. Print out matrix\n";
		cout << "3. Add 2 matrices\n";
		cout << "4. Exit\n";

		switch (choice)
		{
		case 1: s.readElements(); break;
		case 2: s.printMatrix(); break;
		case 4: return 0; break;
		default: cout << "Please enter a valid number!\n"; break;
		}

	}

	return 0;
}