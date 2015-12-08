// invert.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <boost/algorithm/string/trim.hpp>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

const int8_t MATRIX3_SIZE = 3;
const int8_t MATRIX2_SIZE = 2;
const int PRINT_PRECISION = 3;

typedef double Matrix3[MATRIX3_SIZE][MATRIX3_SIZE];
typedef double Matrix2[MATRIX2_SIZE][MATRIX2_SIZE];

bool ReadMatrixFromFile(Matrix3 & matrix, ifstream & file);
string ReadLineFromFile(ifstream & file, bool trim = true);

bool CalculateInverseMatrix(Matrix3 const & sourceMatrix, Matrix3 & inverseMatrix);
double CalculateDeterminant(Matrix3 const & matrix);
double CalculateDeterminant(Matrix2 const & matrix);
double CalculateMinor(Matrix3 const & matrix, int8_t row, int8_t column);
void CalculateMinorMatrix(Matrix3 const & matrix, Matrix3 & minorMatrix);

void TransposeMatrix(Matrix3 const & matrix, Matrix3 & transposedMatrix);
void MultiplyMatrixByDouble(Matrix3 & matrix, double factor);

void PrintMatrix(Matrix3 const & matrix, int precision);

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments number!" << endl
			 << "Usage:" << endl
			 << "\tinvert.exe <matrix file>" << endl;
		return 1;
	}

	ifstream inputFile(argv[1]);
	if (!inputFile.is_open())
	{
		cout << "Error! Can't open specified file \"" << argv[1] << "\"." << endl;
		return 1;
	}

	Matrix3 sourceMatrix;
	bool matrixIsCorrect = ReadMatrixFromFile(sourceMatrix, inputFile);
	if (!matrixIsCorrect)
	{
		cout << "Error! Input file contains invalid definition of the matrix." << endl;
		return 1;
	}

	Matrix3 inverseMatrix;
	bool inverseMatrixIsFound = CalculateInverseMatrix(sourceMatrix, inverseMatrix);
	if (inverseMatrixIsFound)
	{
		PrintMatrix(inverseMatrix, PRINT_PRECISION);
	}
	else
	{
		cout << "The matrix doesn't have inverse." << endl;
	}

	return 0;
}

bool ReadMatrixFromFile(Matrix3 & matrix, ifstream & file)
{
	int8_t i = 0, j = 0;
	while (!file.eof())
	{
		string line = ReadLineFromFile(file);
		if (line.empty())
		{
			continue;
		}

		if (i == MATRIX3_SIZE)
		{
			return false;
		}

		istringstream lineStream(line);
		double matrixItem;
		for (j = 0; !lineStream.eof(); j++)
		{
			lineStream >> matrixItem;

			if ((j == MATRIX3_SIZE) || lineStream.fail())
			{
				return false;
			}

			matrix[i][j] = matrixItem;
		}

		i++;
	}

	return ((i == MATRIX3_SIZE) && (j == MATRIX3_SIZE));
}

string ReadLineFromFile(ifstream & file, bool trim)
{
	string line;
	getline(file, line);
	
	if (trim)
	{
		boost::algorithm::trim<string>(line);
	}

	return line;
}

bool CalculateInverseMatrix(Matrix3 const & sourceMatrix, Matrix3 & inverseMatrix)
{
	double determinant = CalculateDeterminant(sourceMatrix);
	if (determinant == 0)
	{
		return false;
	}

	Matrix3 minorMatrix;
	CalculateMinorMatrix(sourceMatrix, minorMatrix);
	TransposeMatrix(minorMatrix, inverseMatrix);
	
	double factor = (1 / determinant);
	MultiplyMatrixByDouble(inverseMatrix, factor);

	return true;
}

double CalculateDeterminant(Matrix3 const & matrix)
{
	double determinant = 0;
	for (int8_t i = 0; i < MATRIX3_SIZE; i++)
	{
		determinant += (matrix[0][i] * CalculateMinor(matrix, 0, i));
	}

	return determinant;
}

double CalculateDeterminant(Matrix2 const & matrix)
{
	return (matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]);
}

double CalculateMinor(Matrix3 const & matrix, int8_t row, int8_t column)
{
	Matrix2 minorMatrix;
	for (int8_t i = 0, j, k = 0, l; i < MATRIX3_SIZE; i++)
	{
		if (i == row)
		{
			continue;
		}

		for (j = 0, l = 0; j < MATRIX3_SIZE; j++)
		{
			if (j == column)
			{
				continue;
			}

			minorMatrix[k][l] = matrix[i][j];
			l++;
		}

		k++;
	}

	double minor = CalculateDeterminant(minorMatrix);

	return ((row + column) % 2) ? -minor : minor;
}

void CalculateMinorMatrix(Matrix3 const & matrix, Matrix3 & minorMatrix)
{
	for (int8_t i = 0; i < MATRIX3_SIZE; i++)
	{
		for (int8_t j = 0; j < MATRIX3_SIZE; j++)
		{
			minorMatrix[i][j] = CalculateMinor(matrix, i, j);
		}
	}
}

void TransposeMatrix(Matrix3 const & matrix, Matrix3 & transposedMatrix)
{
	for (int8_t i = 0; i < MATRIX3_SIZE; i++)
	{
		for (int8_t j = 0; j < MATRIX3_SIZE; j++)
		{
			transposedMatrix[j][i] = matrix[i][j];
		}
	}
}

void MultiplyMatrixByDouble(Matrix3 & matrix, double factor)
{
	for (int8_t i = 0; i < MATRIX3_SIZE; i++)
	{
		for (int8_t j = 0; j < MATRIX3_SIZE; j++)
		{
			matrix[i][j] *= factor;
		}
	}
}

void PrintMatrix(Matrix3 const & matrix, int precision)
{
	cout << fixed;

	for (int8_t i = 0; i < MATRIX3_SIZE; i++)
	{
		for (int8_t j = 0; j < MATRIX3_SIZE; j++)
		{
			cout << setprecision(precision) << matrix[i][j] << " ";
		}

		cout << endl;
	}

	cout << scientific;
}