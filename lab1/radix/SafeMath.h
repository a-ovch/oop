#pragma once

int SafeAddition(int a, int b, bool & wasOverflow);
int SafeMultiply(int a, int b, bool & wasOverflow);
int SafePow(int base, int exponent, bool & wasOverflow);