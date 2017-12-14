#include <iostream>
#include <iomanip>
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h> 
using namespace std;

void DynamicArray(int SIZE, int start, int increment) //Demo 1. Accepts Array Size, Array Starting value and Array increment value. Returns nothing
{
	int *dynamicArray = new int[SIZE]; //Create location to store array in memory.
	int i = 0;
	dynamicArray[i] = start; //Set start value

	for (i = 1; i < SIZE; i++) //Fill array using increment value
	{
		dynamicArray[i] = start + increment;
		start = start + increment;
	}
	cout << endl;
	cout << "Array" << endl;
	for (i = 0; i < SIZE; i++) //Display array
	{
		cout << setw(2) << dynamicArray[i] << " ";
	}
	cout << "\n" << endl;
	
	delete[] dynamicArray; //Clear the array
	return;
}
void RandomArray() //Demo 2.
{
	const int SIZE = 9;
	int matrix[SIZE][SIZE];
	int *PtrMatrix = (int*)matrix;
	//Random Number Generated Matrix
	srand(time(NULL));
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			*(PtrMatrix + i*9 + j) = rand() % 899 + 100;
		}
	}
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << setw(4) << *(PtrMatrix + i * 9 + j) << " ";
		}
		cout << endl;
	}
	cout << "\n" << endl;
	return;
}

void PointerFunction(float* a, float* b, float* c, float* d, float* e) //Demo 3. Accepts 5 pointers to float values and returns nothing
{
	cout << fixed << setprecision(2) << "The average is " << (*a + *b + *c + *d + *e) / 5 << endl;
	cout << "\n" << endl;
	return;
}
void main()
{
	int operation, SIZE, start, increment, x = 1, input_count;
	float a, b, c, d, e, input_temp;
	float *PtrA = &a, *PtrB = &b, *PtrC = &c, *PtrD = &d, *PtrE = &e;
	string filename;
	//Menu
	do
	{
		cout << "1. Dynamic Array\n2. Random Array\n3. Calculate Average\n4. Exit\n";
		cin >> operation;
		cout << endl;
		if (cin.fail())//Error Checking
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			operation = 0;
		}
		switch (operation)
		{
		case 1:
			
			while (1)
			{
				cout << "Enter number of Elements" << endl;
				cin >> SIZE;
				if (cin.fail())//Error Checking
				{
					cin.clear();
					cin.ignore(INT_MAX, '\n');
				}
				if (SIZE < 1)//Error Checking
				{
					//Do Nothing
				}
				else
				{
					break;
				}
			}
			
			while(1)
			{ 
				cout << "Enter starting value" << endl;
				cin >> start;
				if (cin.fail())//Error Checking
				{
					cin.clear();
					cin.ignore(INT_MAX, '\n');
				}
				if (start < 0)//Error Checking
				{
					//Do Nothing
				}
				else
				{
					break;
				}
			}
			
			while(1)
			{ 
				cout << "Enter increment value" << endl;
				cin >> increment;
				if (cin.fail())//Error Checking
				{
					cin.clear();
					cin.ignore(INT_MAX, '\n');
				}
				if (increment < 0)//Error Checking
				{
					//Do Nothing
				}
				else
				{
					break;
				}
			}
			DynamicArray(SIZE, start, increment);
			break;
		case 2:
			RandomArray();
			break;
		case 3:
			cout << "Please Enter 5 numbers (The average will be calculated)" << endl;
			while (1)
			{
				input_temp = 0;
				cout << "Please Enter Value " << input_count << endl;
				cin >> input_temp;
				if (cin.fail())//Error Checking
				{
					cin.clear();
					cin.ignore(INT_MAX, '\n');
				}
				else
				{
					switch(input_count)
					{
					case 1:
						a = input_temp;
					case 2:
						b = input_temp;
					case 3: 
						c = input_temp;
					case 4:
						d = input_temp;
					case 5:
						e = input_temp;
					}
					input_count++;
					if(input_count == 6)
					{
						break;
					}	
				}
			}
			PointerFunction(PtrA, PtrB, PtrC, PtrD, PtrE);
			break;
		case 4:
			//Exit
			break;
		default:
			cout << "invalid input" << endl;
			cout << endl;
			break;
		}
	} while (operation != 4);
}