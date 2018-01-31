#include <iostream>

using namespace std;

// Declarations
int size = 12;
int mainMatrices[3][12][12];
int strassenSubMatrices[3][2][2][6][6];
// Submatrices of the main matrices
// {0,1,2} {x value = 0,1} {y value = 0,1}
// 000 001      100 101     200 201
// 001 011      110 111     210 211
int S[10][6][6];
int P[7][6][6];

// Function to request input for the main matrices
void inputMainMatrix(int matrix)
{
	cout << "Please enter the elements for matrix " << matrix << endl;
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			cout << "Please enter the value for Matrix " << matrix << ", position " << i << "," << j << endl;
			cin >> mainMatrices[matrix][i][j];
			// mainMatrices[matrix][i][j] = 1; // For testing purposes
			/* // For testing purposes
			if (i == j) 
			{
				mainMatrices[matrix][i][j] = 1;
			}
			else
			{
				mainMatrices[matrix][i][j] = 0;

			}
			*/
		}
	}
}

// Function to display a main matrix
void displayMainMatrix(int matrix)
{
	cout << "Displaying matrix " << matrix << " now" << endl;
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			cout << mainMatrices[matrix][j][i] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

// Function to divide a main matrix into the sub-matrices
void createSubMatrices(int matrix)
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			strassenSubMatrices[matrix][0][0][i][j] = mainMatrices[matrix][i][j];
		}
	}

	for (int i = 6; i < 12; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			strassenSubMatrices[matrix][1][0][i - 6][j] = mainMatrices[matrix][i][j];
		}
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 6; j < 12; j++)
		{
			strassenSubMatrices[matrix][0][1][i][j - 6] = mainMatrices[matrix][i][j];
		}
	}

	for (int i = 6; i < 12; i++)
	{
		for (int j = 6; j < 12; j++)
		{
			strassenSubMatrices[matrix][1][1][i - 6][j - 6] = mainMatrices[matrix][i][j];
		}
	}
}

// Function to display a sub-matrix (Mainly for troubleshooting)
void displaySubMatrix(int matrix, int xValue, int yValue)
{
	cout << "Displaying sub matrix " << "(" << xValue << ")" << "(" << yValue << ")" << " of matrix " << matrix << " now" << endl;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			cout << strassenSubMatrices[matrix][xValue][yValue][j][i] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

// Function to add matrices
void addMatrices(int sumMatrix, int matrix1, int xValue1, int yValue1, int matrix2, int xValue2, int yValue2) 
{
	for (int i = 0; i < 6; i++) 
	{
		for (int j = 0; j < 6; j++) 
		{
			S[sumMatrix][i][j] = strassenSubMatrices[matrix1][xValue1][yValue1][i][j] + strassenSubMatrices[matrix2][xValue2][yValue2][i][j];
		}
	}
}

// Function to subtract matrices
void minusMatrices(int sumMatrix, int matrix1, int xValue1, int yValue1, int matrix2, int xValue2, int yValue2) 
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++) 
		{
			S[sumMatrix][i][j] = strassenSubMatrices[matrix1][xValue1][yValue1][i][j] - strassenSubMatrices[matrix2][xValue2][yValue2][i][j];
		}
	}
}

// Function to display a sum matrix (Mainly for troubleshooting)
void displaySumMatrix(int matrix)
{
	cout << "Displaying sum matrix " << matrix << " now" << endl;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			cout << S[matrix][j][i] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

// Function to multiply a sub-matrix by a sum matrix
void multiplySubMatrixBySumMatrix(int productMatrix, int subMatrix, int xValue, int yValue, int sumMatrix)
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			for (int k = 0; k < 6; k++)
			{
				P[productMatrix][i][j] += strassenSubMatrices[subMatrix][xValue][yValue][k][j] * S[sumMatrix][i][k];
			}
		}
	}
}

// Function to multiply a sum matrix by a sub-matrix
void multiplySumMatrixBySubMatrix(int productMatrix, int sumMatrix, int subMatrix, int xValue, int yValue)
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			for (int k = 0; k < 6; k++)
			{
				P[productMatrix][i][j] += S[sumMatrix][k][j] * strassenSubMatrices[subMatrix][xValue][yValue][i][k];
			}
		}
	}
}

// Function to multiply a sum matrix by a sum matrix
void multiplySumMatrixBySumMatrix(int productMatrix, int sumMatrix1, int sumMatrix2)
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			for (int k = 0; k < 6; k++)
			{
				P[productMatrix][i][j] += S[sumMatrix1][k][j] * S[sumMatrix2][i][k];
			}
		}
	}
}

// Function to display a sum matrix (Mainly for troubleshooting)
void displayProductMatrix(int matrix)
{
	cout << "Displaying product matrix " << matrix << " now" << endl;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			cout << P[matrix][j][i] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

// Function to create the answer matrix
void createAnswerMatrix()
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			strassenSubMatrices[2][0][0][i][j] = P[4][i][j] + P[3][i][j] - P[1][i][j] + P[5][i][j];
		}
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			strassenSubMatrices[2][0][1][i][j] = P[0][i][j] + P[1][i][j];
		}
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			strassenSubMatrices[2][1][0][i][j] = P[2][i][j] + P[3][i][j];
		}
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			strassenSubMatrices[2][1][1][i][j] = P[4][i][j] + P[0][i][j] - P[2][i][j] - P[6][i][j];
		}
	}
}

// Function to create a main matrix from sub-matrices
void createMainMatrix(int matrix)
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			mainMatrices[matrix][i][j] = strassenSubMatrices[matrix][0][0][i][j];
		}
	}

	for (int i = 6; i < 12; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			mainMatrices[matrix][i][j] = strassenSubMatrices[matrix][1][0][i - 6][j];
		}
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 6; j < 12; j++)
		{
			mainMatrices[matrix][i][j] = strassenSubMatrices[matrix][0][1][i][j - 6];
		}
	}

	for (int i = 6; i < 12; i++)
	{
		for (int j = 6; j < 12; j++)
		{
			mainMatrices[matrix][i][j] = strassenSubMatrices[matrix][1][1][i - 6][j - 6];
		}
	}
}

// Main
int main()
{
	// Program introduction
	cout << "This program will take a n=12 sized matrix A and multiply it with a n=12 sized matrix B" << endl;

	// Inputting the matrices
	inputMainMatrix(0);
	inputMainMatrix(1);

	// Creating sub matrices
	createSubMatrices(0);
	createSubMatrices(1);

	// Calculating sum matrices
	minusMatrices(0,1,0,1,1,1,1);
	addMatrices(1,0,0,0,0,0,1);
	addMatrices(2,0,1,0,0,1,1);
	minusMatrices(3,1,1,0,1,0,0);
	addMatrices(4,0,0,0,0,1,1);
	addMatrices(5,1,0,0,1,1,1);
	minusMatrices(6,0,0,1,0,1,1);
	addMatrices(7,1,1,0,1,1,1);
	minusMatrices(8,0,0,0,0,1,0);
	addMatrices(9,1,0,0,1,0,1);

	// Calculating product matrices
	multiplySubMatrixBySumMatrix(0,0,0,0,0);
	multiplySumMatrixBySubMatrix(1,1,1,1,1);
	multiplySumMatrixBySubMatrix(2,2,1,0,0);
	multiplySubMatrixBySumMatrix(3,0,1,1,3);
	multiplySumMatrixBySumMatrix(4,4,5);
	multiplySumMatrixBySumMatrix(5,6,7);
	multiplySumMatrixBySumMatrix(6,8,9);

	// Calculating the answer matrix
	createAnswerMatrix();
	createMainMatrix(2);

	// Outputting the final matrix
	displayMainMatrix(0);
	displayMainMatrix(1);
	displayMainMatrix(2);

	return 0;
}
