CC=g++
CFLAGS=-std=c++11 -Wall -Wextra -I/usr/include/opencv4
LIBS=`pkg-config --cflags --libs opencv4`

all: secuencial

secuencial: secuencial.cpp
	$(CC) $(CFLAGS) -o secuencial secuencial.cpp $(LIBS)