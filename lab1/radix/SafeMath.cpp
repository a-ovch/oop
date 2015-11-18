#include "stdafx.h"

#include "SafeMath.h"

#include <limits.h>
#include <iostream>

using namespace std;

int SafeAddition(int a, int b, bool & wasOverflow)
{
	if (a > (INT_MAX - b))
	{
		wasOverflow = true;

		cout << "Overflow detected: " << a << " + " << b << endl;

		return 0;
	}

	return (a + b);
}

int SafeMultiply(int a, int b, bool & wasOverflow)
{
	if (b && (a > (INT_MAX / b)))
	{
		wasOverflow = true;

		cout << "Overflow detected: " << a << " * " << b << endl;

		return 0;
	}

	return (a * b);
}

int SafePow(int base, int exponent, bool & wasOverflow)
{
	int result = 1;
	for (int i = 0; i < exponent; i++)
	{
		result = SafeMultiply(result, base, wasOverflow);
		if (wasOverflow)
		{
			return 0;
		}
	}

	return result;
}