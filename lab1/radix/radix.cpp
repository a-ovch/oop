// radix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "SafeMath.h"

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

int ParseRadix(const char *pRadixStr);
char GetCharOffset(bool isCharDigit);

int RadixCharToInt(char ch, int radix, bool & wasError);
char IntToRadixChar(int num);

int StringToInt(const char str[], int radix, bool & wasError);
string IntToString(int n, int radix);

string ReverseString(string const &str);

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
	
	bool wasError = false;
	int decimalInt = StringToInt(argv[3], srcRadix, wasError);
	if (wasError)
	{
		return 1;
	}

	string convertedNumStr = IntToString(decimalInt, destRadix);
	cout << convertedNumStr << endl;

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

char GetCharOffset(bool isCharDigit)
{
	const char DIGIT_OFFSET = '0';
	const char LETTER_OFFSET = ('A' - 10);
	return isCharDigit ? DIGIT_OFFSET : LETTER_OFFSET;
}

int RadixCharToInt(char ch, int radix, bool & wasError)
{
	bool isDigit = ((ch >= '0') && (ch <= '9'));
	bool isLetter = ((ch >= 'A') && (ch <= 'Z'));
	if (!(isDigit || isLetter))
	{
		wasError = true;
		cout << "Illegal symbol \"" << ch << "\" was detected." << endl;

		return 0;
	}

	char offset = GetCharOffset(isDigit);
	int decimalNumber = static_cast<int>(ch - offset);
	if (decimalNumber >= radix)
	{
		wasError = true;
		cout << "Illegal character \"" << ch << "\" for radix " << radix << endl;

		return 0;
	}

	return decimalNumber;
}

char IntToRadixChar(int num)
{
	bool isDigit = (num <= 9);
	char offset = GetCharOffset(isDigit);
	return static_cast<char>(num + offset);
}

int StringToInt(const char str[], int radix, bool & wasError)
{
	int decimalNum = 0;
	bool isNegative = false;

	int strLen = static_cast<int>(strlen(str));
	for (int i = 0, power = (strLen - 1); i < strLen; i++, power--)
	{
		char ch = str[i];
		if ((i == 0) && (ch == '-'))
		{
			isNegative = true;
			continue;
		}

		int currentDigit = RadixCharToInt(ch, radix, wasError);
		if (wasError)
		{
			return 0;
		}

		int factor = SafePow(radix, power, wasError);
		if (wasError)
		{
			return 0;
		}
		
		int addition = SafeMultiply(currentDigit, factor, wasError);
		if (wasError)
		{
			return 0;
		}

		decimalNum = SafeAddition(decimalNum, addition, wasError);
		if (wasError)
		{
			return 0;
		}
	}

	return isNegative ? -decimalNum : decimalNum;
}

string IntToString(int n, int radix)
{
	bool isNegative = (n < 0);
	n = abs(n);

	string result("");
	while (n >= radix)
	{
		int decimalDigit = (n % radix);
		result += IntToRadixChar(decimalDigit);;

		n = (n / radix);
	}

	result += IntToRadixChar(n);

	if (isNegative)
	{
		result += "-";
	}

	return ReverseString(result);
}

string ReverseString(string const &str)
{
	string reversedStr("");
	for (string::const_reverse_iterator rit = str.rbegin(); rit != str.rend(); rit++)
	{
		reversedStr += *rit;
	}

	return reversedStr;
}