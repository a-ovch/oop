// radix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

const int MIN_NOTATION = 2;
const int MAX_NOTATION = 36;

int ParseNotation(const char *pNotationStr);

int StringToInt(const char str[], int radix, bool & wasError);
// void IntToString(int n, int radix, char str[], int bufferLength, bool & wasError);

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "Invalid arguments number!" << endl
			 << "Usage:" << endl
			 << "\tradix.exe <source notation> <destination notation> <value>" << endl;
		return 1;
	}

	int srcNotation = ParseNotation(argv[1]);
	if (!srcNotation)
	{
		return 1;
	}

	int destNotation = ParseNotation(argv[2]);
	if (!destNotation)
	{
		return 1;
	}

	char *pNumStr = argv[3];

	// StringToInt
	// IntToString

    return 0;
}

int ParseNotation(const char *pNotationStr)
{
	int notation = atoi(pNotationStr);
	bool isValid = (notation >= MIN_NOTATION) && (notation <= MAX_NOTATION);
	if (!isValid)
	{
		cout << "Notation value \"" << pNotationStr << "\" is invalid." << endl
			 << "It must be between " << MIN_NOTATION << " and " << MAX_NOTATION << endl;

		notation = 0;
	}

	return notation;
}

int StringToInt(const char str[], int radix, bool & wasError)
{

}
