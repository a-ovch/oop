@echo off

echo Test empty input
radix.exe > output.txt
IF NOT ERRORLEVEL 1 GOTO error

echo Test incorrect arguments number
radix.exe 1 2 3 4 5 > output.txt
IF NOT ERRORLEVEL 1 GOTO error

echo Test invalid radix value
radix.exe 37 10 2 > output.txt
IF NOT ERRORLEVEL 1 GOTO error

echo Test invalid input number
radix.exe 2 10 3 > output.txt
IF NOT ERRORLEVEL 1 GOTO error

echo Test overflow
radix.exe 36 10 ZZZZZZZZZZZZZZZZZZZ > output.txt
IF NOT ERRORLEVEL 1 GOTO error

echo Test convertion 101(2) == 5(10)
radix.exe 2 10 101 > output.txt
IF ERRORLEVEL 1 GOTO error

FC output.txt output1.txt
IF ERRORLEVEL 1 GOTO error

echo Test convertion -2048(10) == -800(16)
radix.exe 10 16 -2048 > output.txt
IF ERRORLEVEL 1 GOTO error

FC output.txt output2.txt
IF ERRORLEVEL 1 GOTO error

echo Test convertion CAT(30) == 248B(17)
radix.exe 30 17 CAT > output.txt
IF ERRORLEVEL 1 GOTO error

FC output.txt output3.txt
IF ERRORLEVEL 1 GOTO error

echo Test convertion 0(3) == 0(32)
radix.exe 3 32 0 > output.txt
IF ERRORLEVEL 1 GOTO error

FC output.txt output4.txt
IF ERRORLEVEL 1 GOTO error

echo Test convertion ABC(16) == ABC(16)
radix.exe 16 16 ABC > output.txt
IF ERRORLEVEL 1 GOTO error

FC output.txt output5.txt
IF ERRORLEVEL 1 GOTO error

echo Test convertion 2147483647(10) == 2147483647(10)
radix.exe 10 10 2147483647 > output.txt
IF ERRORLEVEL 1 GOTO error

FC output.txt output6.txt
IF ERRORLEVEL 1 GOTO error

echo Test convertion -2147483648(10) == -2147483648(10)
radix.exe 10 10 -2147483648 > output.txt
IF ERRORLEVEL 1 GOTO error

FC output.txt output7.txt
IF ERRORLEVEL 1 GOTO error


echo All tests successfully passed!
GOTO clean

:error
echo Test has failed!
GOTO clean

:clean
DEL output.txt
exit
