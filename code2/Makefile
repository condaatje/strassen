OBJS = Main.o Helpers.o Strassen.o Tests.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c -std=c++11 -Ofast $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all: strassen

strassen : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o strassen

Main.o : Main.hpp Helpers.hpp Tests.cpp
	$(CC) $(CFLAGS) Main.cpp

Helpers.o : Helpers.hpp
	$(CC) $(CFLAGS) Helpers.cpp

Strassen.o : Strassen.hpp Helpers.hpp
	$(CC) $(CFLAGS) Strassen.cpp

Tests.o : Tests.hpp Strassen.hpp Helpers.hpp
	$(CC) $(CFLAGS) Tests.cpp


clean:
	rm ./*.o
