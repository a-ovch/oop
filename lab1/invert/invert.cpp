// invert.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <fstream>

using namespace std;

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

    return 0;
}

