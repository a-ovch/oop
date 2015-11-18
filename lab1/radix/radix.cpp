// radix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "SafeMath.h"

#include <iostream>
#include <memory>
#include <stdlib.h>

using namespace std;

int ParseRadix(const char *pRadixStr);
int GetOutputBufferSize();
char GetCharOffset(bool isCharDigit);

int RadixCharToInt(char ch, int radix, bool & wasError);
char IntToRadixChar(int num);

int StringToInt(const char str[], int radix, bool & wasError);
void IntToString(int n, int radix, char str[], int bufferLength, bool & wasError);

void ReverseBuffer(char buffer[], int bufferLength);

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

	int bufferSize = GetOutputBufferSize();
	auto convertedNumStr = make_unique<char[]>(bufferSize);

	IntToString(abs(decimalInt), destRadix, convertedNumStr.get(), bufferSize, wasError);
	
	if (wasError)
	{
		return 1;
	}

	if (decimalInt < 0)
	{
		cout << "-";
	}
	cout << convertedNumStr.get() << endl;

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

int GetOutputBufferSize()
{
	const int BITS_IN_BYTE = 8;
	return sizeof(int) * BITS_IN_BYTE;
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

void IntToString(int n, int radix, char str[], int bufferLength, bool & wasError)
{
	int i = 0;
	while (n >= radix)
	{
		int decimalDigit = (n % radix);
		char charDigit = IntToRadixChar(decimalDigit);
		str[i] = charDigit;

		n = (n / radix);
		i++;

		if (i == (bufferLength - 1))
		{
			wasError = true;
			cout << "Size of buffer " << bufferLength << " is inadequate to write output number." << endl;
			return;
		}
	}

	str[i] = IntToRadixChar(n);
	str[i + 1] = '\0';

	ReverseBuffer(str, (i + 1));
}

void ReverseBuffer(char buffer[], int bufferLength)
{
	char tmp;
	for (int i = 0, j = (bufferLength - 1); i < j; i++, j--)
	{
		tmp = buffer[j];
		buffer[j] = buffer[i];
		buffer[i] = tmp;
	}
}