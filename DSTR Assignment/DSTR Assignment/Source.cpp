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
	int rowPos, columnPos, element;
	row *first = NULL, *current = NULL;

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
	totalRow = rows;
	totalCol = columns;

	cout << "The sparse matrix with " << totalRow << " and " << totalCol << " has been created!\n";
}

SM::SM()
{

}

SM::~SM()
{

}

void SM::readElements()
{
	row *tempRow = new row;
	column *tempCol = new column;
	row *checkRow = new row;

	cout << "\nEnter the row you want to input: ";
	cin >> rowPos;
	cout << "Enter the column you want to input: ";
	cin >> columnPos;
	cout << "Enter a non-zero element: ";
	cin >> element;


}

void SM::printMatrix()
{

}

void mainMenu()
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
		cout << "-----------------------------------\n";
		cout << "Enter your choice:";
		cin >> choice;

		switch (choice)
		{
		case 1: s.readElements(); break;
		case 2: s.printMatrix(); break;
		case 4: exit(0); break;
		default: cout << "Please enter a valid number!\n"; break;
		}

	}

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

	mainMenu();
}