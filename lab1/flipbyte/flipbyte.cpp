// flipbyte.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <sstream>

#define BITS_IN_BYTE 8
#define MIN_INPUT_VALUE 0
#define MAX_INPUT_VALUE 255

using namespace std;

unsigned char ReversBits(unsigned char num);

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments number." << endl;
		cout << "Usage:\n\tflipbyte.exe <byte>" << endl;
		return 1;
	}

	istringstream inputData = istringstream(argv[1]);
	int inputNumber;

	if (!(inputData >> inputNumber) || 
		 (inputNumber < MIN_INPUT_VALUE) || 
		 (inputNumber > MAX_INPUT_VALUE))
	{
		cout << "Your input data \"" << argv[1] << "\" is invalid." << endl;
		cout << "It must be 1-byte number from 0 to 255." << endl;
		return 1;
	}

	unsigned char numberToRevers = static_cast<unsigned char>(inputNumber);
	unsigned char reversedNumber = ReversBits(numberToRevers);
	
	cout << static_cast<unsigned short>(reversedNumber) << endl;

    return 0;
}

unsigned char ReversBits(unsigned char num)
{
	const int bitsCount = sizeof(num) * BITS_IN_BYTE;
	const unsigned char eraser = 1;

	unsigned char result = 0;

	for (int i = 0; i < bitsCount; i++)
	{
		result |= ((num >> i) & eraser) << (bitsCount - i - 1);
	}

	return result;
}

