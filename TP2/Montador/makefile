CC = g++
CFLAGS = -O2

all: main.o Module.o
	$(CC) $(CFLAGS) main.o Module.o -o montador.exe

main.o: main.cpp Module.o
	$(CC) $(CFLAGS) -c main.cpp

Module.o: Module.cpp Module.hpp
	$(CC) $(CFLAGS) -c Module.cpp Module.hpp

clean:
	rm *.o  *.gch montador.exe

remake:
	make clean
	make all
