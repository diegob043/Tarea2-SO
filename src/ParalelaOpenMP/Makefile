CC=g++
CFLAGS=-std=c++11 -Wall -Wextra -I/usr/include/opencv4
LIBS=`pkg-config --cflags --libs opencv4` -fopenmp

all: paralelaOpen


paralelaOpen: paralelaOpenMP.cpp
	$(CC) $(CFLAGS) -o paralelaOpen paralelaOpenMP.cpp $(LIBS)