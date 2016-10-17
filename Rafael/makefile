CC = g++
CFLAGS = -O3

all: main.o Linker.o Module.o
	$(CC) $(CFLAGS) main.o Linker.o Module.o -o a.out

main.o: main.cpp Linker.o Module.o
	$(CC) $(CFLAGS) -c main.cpp

Linker.o: Linker.cpp Linker.hpp Module.o
	$(CC) $(CFLAGS) -c Linker.cpp Linker.hpp

Module.o: Module.cpp Module.hpp
	$(CC) $(CFLAGS) -c Module.cpp Module.hpp

clean:
	rm *.o  *~ *.gch a.out
