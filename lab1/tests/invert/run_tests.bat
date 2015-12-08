@echo off

echo Test empty input
invert.exe > output.txt
IF NOT ERRORLEVEL 1 GOTO error

echo Test incorrect arguments number
invert.exe matrix.txt matrix2.txt > output.txt
IF NOT ERRORLEVEL 1 GOTO error

echo Pass nonexistent file
invert.exe nonexistent.txt > output.txt
IF NOT ERRORLEVEL 1 GOTO error

echo Pass file with incorrect input data 1
invert.exe incorrect1.txt > output.txt
IF NOT ERRORLEVEL 1 GOTO error

echo Pass file with incorrect input data 2
invert.exe incorrect2.txt > output.txt
IF NOT ERRORLEVEL 1 GOTO error

echo Pass file with incorrect input data 2
invert.exe incorrect2.txt > output.txt
IF NOT ERRORLEVEL 1 GOTO error

echo Test invert for matrix with determinant == 0
invert.exe matrix1.txt > output.txt
FC output.txt output1.txt
IF ERRORLEVEL GOTO error

echo Try to invert matrix 1
invert.exe matrix2.txt > output.txt
FC output.txt output2.txt
IF ERRORLEVEL 1 GOTO error

echo Try to invert matrix 2
invert.exe matrix3.txt > output.txt
FC output.txt output3.txt
IF ERRORLEVEL 1 GOTO error

echo Try to invert matrix 3
invert.exe matrix4.txt > output.txt
FC output.txt output4.txt
IF ERRORLEVEL 1 GOTO error

echo All tests successfully passed!
GOTO clean

:error
echo Test has failed!
GOTO clean

:clean
DEL output.txt
exit
