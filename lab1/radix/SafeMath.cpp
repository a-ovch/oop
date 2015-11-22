#include "stdafx.h"

#include "SafeMath.h"

#include <limits.h>
#include <iostream>
#include <cassert>

using namespace std;

int SafeAddition(int a, int b)
 {
	bool isOverflow = (b > 0) ? (a > (INT_MAX - b)) : (a < (INT_MIN - b));
	if (isOverflow)
	{
		throw exception("Overflow when adding detected.");
	}

	return (a + b);
}

int SafeMultiply(int a, int b)
{
	if (b && (a > (INT_MAX / b)))
	{
		throw exception("Overflow when multipliing detected.");
	}

	return (a * b);
}