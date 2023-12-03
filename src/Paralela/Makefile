CC=g++
CFLAGS=-std=c++11 -Wall -Wextra -I/usr/include/opencv4
LIBS=`pkg-config --cflags --libs opencv4`

all: paralela


paralela: paralela.cpp
	$(CC) $(CFLAGS) -o paralela paralela.cpp $(LIBS)