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

	SM(int rows, int columns);
	~SM();
	void readElements();
	void printMatrix();
	void insertFirstNumber(node *d);
	void insertLastNumber(node *d);
	void insertFirstRowColNumber(node *d);
	void insertMiddleNumber(node *d);
	void addSM(SM *newMatrix);
};

SM::SM(int rows, int columns)
{
	totalRow = rows;
	totalCol = columns;
}

//Destructor for freeing memory allocation of linked list
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

//Insert on the first head node of the linked list
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

//Insert on the last node of the linked list
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

//Insert the value on the first row and column indexes
void SM::insertFirstRowColNumber(node *d)
{
	node *temp = new node;

	temp = (struct node *) malloc(sizeof(struct node));
	temp->rowIndex = d->rowIndex;
	temp->columnIndex = d->columnIndex;
	temp->value = d->value;
	
	temp->next = head;
	head = temp;
}

//Insert the value between the head and tail node of the linked list, depending on the row and column index
void SM::insertMiddleNumber(node *d)
{
	node *temp = new node;
	node *prev = head;

	temp = (struct node *) malloc(sizeof(struct node));
	temp->rowIndex = d->rowIndex;
	temp->columnIndex = d->columnIndex;
	temp->value = d->value;

	temp->next = prev->next;
	prev->next = temp;
}

template<typename T> void printValue(T t, const int& width)
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
	
	//Validation
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
		//If the row and column indexes are 1, insert at this position as head node
		else if (newData->rowIndex == 1 && newData->columnIndex == 1)
		{
			insertFirstRowColNumber(newData);
		}
		//If the linked list is not empty (There is head node), execute this statement
		else if (temp != NULL)
		{
			//Looping through the temp to compare the input row and column with the temp row and column
			while (temp != NULL)
			{
				//If the temp row and column is bigger than the input row and column, insert the node in the middle of the linked list
				if (newData->rowIndex < temp->rowIndex + 1 && newData->columnIndex < temp->columnIndex + 1)
				{
					insertMiddleNumber(newData);
					break;
				}
				//If not, traverse to the next node and check for condition
				else
				{
					temp = temp->next;
				}
			}

			//Insert the node as the tail of the linked list if its equal to the total row and column which is the last
			if (newData->rowIndex == totalRow && newData->columnIndex == totalCol)
			{
				insertLastNumber(newData);
			}
			else
			{
				insertLastNumber(newData);
			}
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
							printValue(temp->value, colWidth);
							temp = temp->next;
						}
						else
						{
							printValue(0, colWidth);
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
					printValue(0, colWidth);
				}
			}
			cout << endl;
		}
	}
}

//Addition algorithm for matrices (Between 2 sparse matrix)
void SM::addSM(SM *secondMatrix)
{
	node *firstM = new node;
	node *secondM = new node;
	node *list = new node;
	node *newM = new node;

	firstM = this->head;
	secondM = secondMatrix->head;
	list = NULL; newM = NULL;

	while (firstM != NULL || secondM != NULL)
	{
		node *temp = new node;
		if (firstM == NULL)
		{
			list->next = secondM;
			break;

		}
		else if (secondM == NULL)
		{
			list->next = firstM;
			break;
		}
		//Comparing the value of row between 2 matrices
		//If both matrices having the same row index
		if (firstM->rowIndex == secondM->rowIndex)
		{
			if (firstM->columnIndex < secondM->columnIndex)
			{
				temp->rowIndex = firstM->rowIndex;
				temp->columnIndex = firstM->columnIndex;
				temp->value = firstM->value;
				temp->next = NULL;
				firstM = firstM->next;
			}
			else if (firstM->columnIndex > secondM->columnIndex)
			{
				temp->rowIndex = secondM->rowIndex;
				temp->columnIndex = secondM->columnIndex;
				temp->value = secondM->value;
				temp->next = NULL;
				firstM = firstM->next;
				secondM = secondM->next;
			}
			//If both first matrix and second matrix column are the same, sum it up
			else if (firstM->columnIndex == secondM->columnIndex)
			{
				temp->rowIndex = firstM->rowIndex;
				temp->columnIndex = firstM->columnIndex;
				temp->value = firstM->value + secondM->value;
				temp->next = NULL;
				firstM = firstM->next;
				secondM = secondM->next;
			}
			if (newM == NULL)
			{
				newM = temp;
				list = temp;
			}
			else 
			{
				list->next = temp;
				list = list->next;
			}
		}
		//If the row index of the first matrix is bigger than the second matrix
		else if (firstM->rowIndex > secondM->rowIndex)
		{
			temp->rowIndex = secondM->rowIndex;
			temp->columnIndex = secondM->columnIndex;
			temp->value = secondM->value;
			temp->next = NULL;
			secondM = secondM->next;

			if (newM == NULL)
			{
				newM = temp;
				list = temp;

			}
			else
			{
				list->next = temp;
				list = list->next;
			}

		}
		//If the row index of second matrix is bigger than the first one
		else if (firstM->rowIndex < secondM->rowIndex)
		{
			temp->rowIndex = firstM->rowIndex;
			temp->columnIndex = firstM->columnIndex;
			temp->value = firstM->value;
			temp->next = NULL;
			firstM = firstM->next;

			if (newM == NULL)
			{
				newM = temp;
				list = temp;

			}
			else
			{
				list->next = temp;
				list = list->next;
			}

		}
		
	}

	//Newly added matrix to be displayed
	SM *newMatrix = new SM(totalRow, totalCol);
	newMatrix->head = newM;
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