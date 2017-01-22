CC = gcc
CFLAGS = -O3

all: main.o snake.o queue.o pair.o
	$(CC) $(CFLAGS) main.o snake.o queue.o pair.o -o sb.exe

main.o: main.c snake.o queue.o pair.o
	$(CC) $(CFLAGS) -c main.c

snake.o: snake.c snake.h queue.o pair.o
	$(CC) $(CFLAGS) -c snake.c snake.h

queue.o: queue.c queue.h pair.o
	$(CC) $(CFLAGS) -c queue.c queue.h

pair.o: pair.c pair.h
	$(CC) $(CFLAGS) -c pair.c pair.h

clean:
	rm *.o  *.gch sb.exe

remake:
	make clean
	make all
