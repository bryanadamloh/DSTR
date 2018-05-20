#include <iostream>
#include <stdlib.h>
#include <iomanip>

using namespace std;

struct node
{
	int rowIndex;
	int columnIndex;
	int value;
	struct node *next;
};

class SM 
{
	int rowPos, columnPos, num;
	node *head = NULL, *tail = NULL;

public:
	int totalRow, totalCol;

	SM();
	SM(int rows, int columns);
	~SM();
	void readElements();
	void printMatrix();
	void insertFirstNumber(node *d);
	void insertLastNumber(node *d);
	void addSM(SM *newMatrix);
};

SM::SM(int rows, int columns)
{
	totalRow = rows;
	totalCol = columns;
}

SM::SM()
{

}

SM::~SM()
{
	node * temp = head;

	while (temp != NULL) 
	{
		temp = temp->next;
		delete head;
		head = temp;
	}
	head = NULL;
	tail = NULL;

	cout << "Sparse Matrix has been successfully deleted!\n";
}

void SM::insertFirstNumber(node *d)
{
	node *temp = new node;

	temp = (struct node *) malloc(sizeof(struct node));
	temp->rowIndex = d->rowIndex;
	temp->columnIndex = d->columnIndex;
	temp->value = d->value;
	temp->next = NULL;

	head = temp;
	tail = temp;
	temp = NULL;
}

void SM::insertLastNumber(node *d)
{
	node *temp = new node;

	temp = (struct node *) malloc(sizeof(struct node));
	temp->rowIndex = d->rowIndex;
	temp->columnIndex = d->columnIndex;
	temp->value = d->value;
	temp->next = NULL;

	tail->next = temp;
	tail = temp;
}

template<typename T> void printElement(T t, const int& width)
{
	const char separator = ' ';
	cout << left << setw(width) << setfill(separator) << t;
}

//Input non-zero elements into the matrix
void SM::readElements()
{
	node *newData = new node;
	node *temp = head;

	cout << "\nEnter the row you want to input: ";
	cin >> rowPos;
	cout << "Enter the column you want to input: ";
	cin >> columnPos;
	cout << "Enter a non-zero element: ";
	cin >> num;

	newData->rowIndex = rowPos;
	newData->columnIndex = columnPos;
	newData->value = num;
	newData->next = NULL;
	
	//If row or column is more than the total row and column given
	if (rowPos > totalRow || columnPos > totalCol)
	{
		cout << "Invalid Row/Column Position!\n";
	}
	//Linked list can only be added from the beginning and the end
	else
	{
		//If the linked list is empty
		if (head == NULL)
		{
			insertFirstNumber(newData);
		}
		//If there are linked list existed, add to the tail of the linked list
		else
		{
			insertLastNumber(newData);
		}

		cout << "You have succesfully entered a number!\n";
	}
}

//Display matrix
void SM::printMatrix()
{
	node *temp = head;
	int rowWidth = totalRow;
	int colWidth = totalCol;
	int i, j;

	//If the linked list is empty
	if (temp == NULL)
	{
		cout << "Sparse Matrix is empty!\n";
	}
	//If there is non-zero elements in the linked list
	else
	{
		for (i = 0; i < totalRow; i++)
		{
			cout << setw(rowWidth);

			for (j = 0; j < totalCol; j++)
			{
				temp = head;
				bool condition = false;

				//Using while loop to check condition within the column of the matrix
				while (temp != NULL)
				{
					//If the row and column matches with the for loop condition, execute this block
					if (temp->rowIndex - 1 == i && temp->columnIndex - 1 == j)
					{
						if (temp->value != NULL)
						{
							condition = true;
							printElement(temp->value, colWidth);
							temp = temp->next;
						}
						else
						{
							printElement(0, colWidth);
						}
					}
					//This statement traverse the node to the next node, and compare the row and column index again with the for loop condition
					else
					{
						temp = temp->next;
					}
				}
				if (condition == false)
				{
					printElement(0, colWidth);
				}
			}

			cout << endl;
		}
	}
}

//Addition algorithm for matrices (Between 2 sparse matrix)
void SM::addSM(SM *secondMatrix)
{
	node *matrixA = new node;
	node *matrixB = new node;

	matrixA = this->head;
	matrixB = secondMatrix->head;

	node *templist = new node;
	templist = NULL;
	node *start = new node;
	start = NULL;

	while (matrixA != NULL || matrixB != NULL) 
	{
		node *temp = new node;
		if (matrixA == NULL) 
		{
			templist->next = matrixB;
			break;

		}
		else if (matrixB == NULL)
		{
			templist->next = matrixA;
			break;
		}
		//Comparing the value of row between 2 matrices
		//If both matrices having the same row index
		if (matrixA->rowIndex == matrixB->rowIndex)
		{
			if (matrixA->columnIndex == matrixB->columnIndex) 
			{
				temp->rowIndex = matrixA->rowIndex;
				temp->columnIndex = matrixA->columnIndex;
				temp->value = matrixA->value + matrixB->value;
				temp->next = NULL;
				matrixA = matrixA->next;
				matrixB = matrixB->next;

			}
			else if (matrixA->columnIndex < matrixB->columnIndex)
			{
				temp->rowIndex = matrixA->rowIndex;
				temp->columnIndex = matrixA->columnIndex;
				temp->value = matrixA->value;
				temp->next = NULL;
				matrixA = matrixA->next;

			}
			else if (matrixA->columnIndex > matrixB->columnIndex) 
			{
				temp->rowIndex = matrixB->rowIndex;
				temp->columnIndex = matrixB->columnIndex;
				temp->value = matrixB->value;
				temp->next = NULL;
				matrixA = matrixA->next;
				matrixB = matrixB->next;
			}
			if (start == NULL) 
			{
				start = temp;
				templist = temp;
			}
			else 
			{
				templist->next = temp;
				templist = templist->next;
			}
		}
		//If the row index of second matrix is bigger than the first one
		else if (matrixA->rowIndex < matrixB->rowIndex) 
		{
			temp->rowIndex = matrixA->rowIndex;
			temp->columnIndex = matrixA->columnIndex;
			temp->value = matrixA->value;
			temp->next = NULL;
			matrixA = matrixA->next;

			if (start == NULL)
			{
				start = temp;
				templist = temp;

			}
			else
			{
				templist->next = temp;
				templist = templist->next;
			}

		}
		//If the row index of the first matrix is bigger than the second matrix
		else if (matrixA->rowIndex > matrixB->rowIndex) 
		{
			temp->rowIndex = matrixB->rowIndex;
			temp->columnIndex = matrixB->columnIndex;
			temp->value = matrixB->value;
			temp->next = NULL;
			matrixB = matrixB->next;

			if (start == NULL)
			{
				start = temp;
				templist = temp;

			}
			else
			{
				templist->next = temp;
				templist = templist->next;
			}

		}
	}

	SM *newMatrix = new SM(totalRow, totalCol);
	newMatrix->head = start;
	cout << "New Matrix:\n";
	newMatrix->printMatrix();
}

//Main menu for inserting, adding and deleting matrices
void mainMenu(SM& first, SM& second)
{
	int choice;

	while (1)
	{
		cout << "\n-----------------------------------\n";
		cout << "  Sparse Matrix using Linked List  \n";
		cout << "-----------------------------------\n";
		cout << "1. Add Elements in First Matrix\n";
		cout << "2. Add Elements in Second Matrix\n";
		cout << "3. Print First Matrix\n";
		cout << "4. Print Second Matrix\n";
		cout << "5. Matrix Addition\n";
		cout << "6. Delete First Matrix\n";
		cout << "7. Delete Second Matrix\n";
		cout << "8. Exit\n";
		cout << "-----------------------------------\n";
		cout << "Enter your choice:";
		cin >> choice;

		switch (choice)
		{
			case 1: first.readElements(); break;
			case 2: second.readElements(); break;
			case 3: first.printMatrix(); break;
			case 4: second.printMatrix(); break;
			case 5: first.addSM(&second); break;
			case 6: first.~SM(); break;
			case 7: second.~SM(); break;
			case 8: exit(0);
			default: cout << "Please enter a valid number!\n"; break;
		}

	}
}

//Initialize rows and columns for both matrices
int main()
{
	int row, column;

	cout << "Sparse Matrix using Linked List\n";

	do 
	{
		cout << "Enter the number of rows of the matrix:\n";
		cin >> row;
		cout << "Enter the number of columns of the matrix:\n";
		cin >> column;

		if (row <= 0 || column <= 0)
		{
			cout << "The number of rows and columns must be more than zero!\n" << endl;
		}
	} while (row <= 0 || column <= 0);
	

	//Creating 2 constructors for adding both matrix
	SM a(row, column);
	SM b(row, column);

	cout << "The sparse matrices with " << row << " and " << column << " has been created!\n";

	mainMenu(a, b);
}