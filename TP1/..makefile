CC = g++
CFLAGS = -g3 -O3

all: main.o instructions.o maps.o
	$(CC) $(CFLAGS) main.o instructions.o maps.o -o a.out

main.o: main.cpp instructions.o maps.o
	$(CC) $(CFLAGS) -c main.cpp

instructions.o: instructions.cpp instructions.h maps.o
	$(CC) $(CFLAGS) -c instructions.cpp instructions.h

maps.o: maps.cpp maps.h
	$(CC) $(CFLAGS) -c maps.cpp maps.h

clean:
	rm *.o  *~ *.gch a.out
