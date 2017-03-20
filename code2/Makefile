
OBJS = Main.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c -std=c++11 -Ofast $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all: strassen

strassen : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o strassen

Main.o : Main.hpp
	$(CC) $(CFLAGS) Main.cpp

clean:
	rm ./*.o
