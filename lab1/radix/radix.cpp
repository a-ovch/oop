// radix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <memory>
#include <stdlib.h>
#include <math.h>

using namespace std;

int ParseRadix(const char *pRadixStr);
int GetOutputBufferSize();
char GetCharOffset(bool isCharDigit);

int CharToInt(char ch, bool & wasError);
char IntToChar(int num);

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

	IntToString(decimalInt, destRadix, convertedNumStr.get(), bufferSize, wasError);
	
	if (wasError)
	{
		return 1;
	}

	cout << "Converted num " << convertedNumStr.get() << endl;

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

int CharToInt(char ch, bool & wasError)
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
	return static_cast<int>(ch - offset);
}

char IntToChar(int num)
{
	bool isDigit = (num <= 9);
	char offset = GetCharOffset(isDigit);
	return static_cast<char>(num + offset);
}

int StringToInt(const char str[], int radix, bool & wasError)
{
	size_t strLen = strlen(str);

	int decimalNum = 0;
	for (size_t i = 0; i < strLen; i++)
	{
		char ch = str[i];
		int currentDigit = CharToInt(ch, wasError);
		if (wasError)
		{
			return 0;
		}

		if (currentDigit >= radix)
		{
			wasError = true;
			cout << "Illegal character \"" << ch << "\" for radix " << radix << endl;

			return 0;
		}

		int power = static_cast<int>(strLen - i - 1);
		int factor = static_cast<int>(pow(radix, power));
		decimalNum += currentDigit * factor;
	}

	return decimalNum;
}

void IntToString(int n, int radix, char str[], int bufferLength, bool & wasError)
{
	int i = 0;
	while (n >= radix)
	{
		int decimalDigit = (n % radix);
		char charDigit = IntToChar(decimalDigit);
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

	str[i] = IntToChar(n);
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