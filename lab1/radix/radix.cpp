// radix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "SafeMath.h"

#include <iostream>
#include <string>
#include <boost/format.hpp>

using namespace std;

int ParseRadix(const char *pRadixStr);
char GetCharOffset(bool isCharDigit);

int RadixCharToInt(char ch, int radix);
char IntToRadixChar(int num);

int StringToInt(const char str[], int radix);
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

	try
	{
		int srcRadix = ParseRadix(argv[1]);
		int destRadix = ParseRadix(argv[2]);

		bool wasError = false;
		int decimalInt = StringToInt(argv[3], srcRadix);
		if (wasError)
		{
			return 1;
		}

		string convertedNumStr = IntToString(decimalInt, destRadix);
		cout << convertedNumStr << endl;
	}
	catch (exception e)
	{
		cout << "Error: " << e.what() << endl;
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
		boost::format errorPattern("Radix value \"%1%\" is invalid.\nIt must be between %2% and %3%");
		errorPattern % pRadixStr % MIN_RADIX % MAX_RADIX;
		throw exception(errorPattern.str().c_str());
	}

	return radix;
}

char GetCharOffset(bool isCharDigit)
{
	const char DIGIT_OFFSET = '0';
	const char LETTER_OFFSET = ('A' - 10);
	return isCharDigit ? DIGIT_OFFSET : LETTER_OFFSET;
}

int RadixCharToInt(char ch, int radix)
{
	bool isDigit = ((ch >= '0') && (ch <= '9'));
	bool isLetter = ((ch >= 'A') && (ch <= 'Z'));
	if (!(isDigit || isLetter))
	{
		boost::format errorPattern("Illegal symbol \"%1%\" was detected.");
		errorPattern % ch;
		throw exception(errorPattern.str().c_str());
	}

	char offset = GetCharOffset(isDigit);
	int decimalNumber = static_cast<int>(ch - offset);
	if (decimalNumber >= radix)
	{	
		boost::format errorPattern("Illegal character \"%1%\" for radix \"%2%\"");
		errorPattern % ch % radix;
		throw exception(errorPattern.str().c_str());
	}

	return decimalNumber;
}

char IntToRadixChar(int num)
{
	bool isDigit = (num <= 9);
	char offset = GetCharOffset(isDigit);
	return static_cast<char>(num + offset);
}

int StringToInt(const char str[], int radix)
{
	int result = 0;
	bool isNegative = false;

	size_t strLen = strlen(str);
	for (size_t i = 0; i < strLen; i++)
	{
		char ch = str[i];
		if ((i == 0) && (ch == '-'))
		{
			isNegative = true;
			continue;
		}

		int currentDigit = RadixCharToInt(ch, radix);
		result = SafeMultiply(result, radix);
		result = SafeAddition(result, currentDigit);
	}

	return isNegative ? -result : result;
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
	for (auto rit = str.rbegin(); rit != str.rend(); rit++)
	{
		reversedStr += *rit;
	}

	return reversedStr;
}