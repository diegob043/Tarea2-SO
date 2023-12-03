CC=g++
CFLAGS=-std=c++11 -Wall -Wextra -I/usr/include/opencv4
LIBS=`pkg-config --cflags --libs opencv4`

all: sequential

sequential: secuencial.cpp
	$(CC) $(CFLAGS) -o sequential secuencial.cpp $(LIBS)