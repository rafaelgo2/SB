CC = g++
CFLAGS = -O2

all: main.o Module.o
ifeq ($(OS),Windows_NT)
	$(CC) $(CFLAGS) main.o Module.o -o montador.exe
else
	$(CC) $(CFLAGS) main.o Module.o -o montador
endif

main.o: main.cpp Module.o
	$(CC) $(CFLAGS) -c main.cpp

Module.o: Module.cpp Module.hpp
	$(CC) $(CFLAGS) -c Module.cpp Module.hpp

clean:
	rm *.o  *.gch montador*

remake:
	make clean
	make all

test:
	./montador tst/W2-0.a tst/W2-0.mif
	./montador tst/W2-1.a tst/W2-1.mif
	./montador tst/W2-2.a tst/W2-2.mif
	./montador tst/W2-3.a tst/W2-3.mif
	./montador tst/W2-4.a tst/W2-4.mif
