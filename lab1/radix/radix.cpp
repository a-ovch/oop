// radix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

int ParseRadix(const char *pRadixStr);

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "Invalid arguments number!" << endl
			 << "Usage:" << endl
			 << "\tradix.exe <source notation> <destination notation> <value>" << endl;
		return 1;
	}

	int srcRadix = ParseRadix(argv[1]);
	if (!srcRadix)
	{
		return 1;
	}

	int destRadix = ParseRadix(argv[2]);
	if (!destRadix)
	{
		return 1;
	}
	

    return 0;
}

int ParseRadix(const char *pRadixStr)
{
	const int MIN_RADIX = 2;
	const int MAX_RADIX = 36;

	int radix = atoi(pRadixStr);
	bool isValid = (radix >= MIN_RADIX) && (radix <= MAX_RADIX);
	if (!isValid)
	{
		cout << "Radix value \"" << pRadixStr << "\" is invalid." << endl
			 << "It must be between " << MIN_RADIX << " and " << MAX_RADIX << endl;
	}

	return isValid ? radix : 0;
}