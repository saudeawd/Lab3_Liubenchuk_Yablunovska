#!/bin/bash
set -e

CXXFLAGS="-std=c++20 -Wall -Wextra -pedantic -Werror=vla -fPIC"
CFLAGS="-Wall -Wextra -pedantic -Werror=vla -fPIC"

rm -r build
mkdir build/
echo "Cleaned build directory"

# library
g++ $CXXFLAGS -c mystring.cpp -o build/mystring.o
g++ $CXXFLAGS -c mystring_c.cpp -o build/mystring_c.o
g++ $CXXFLAGS -shared build/mystring.o build/mystring_c.o -o build/libStrings.so
echo "Successfully compiled strings library"

# main c++
g++ $CXXFLAGS main.cpp build/mystring.o -o build/Main
echo "Successfully compiled c++ demo"

# main c
gcc $CFLAGS main.c build/mystring.o build/mystring_c.o -lstdc++ -o build/MainC
echo "Successfully compiled c demo"

g++ $CXXFLAGS task3.cpp build/mystring.o -o build/Task3
echo "Successfully compiled Task3"