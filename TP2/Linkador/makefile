CC = g++
CFLAGS =  -std=c++11 -O2

all: main.o Linker.o ObjectModule.o
ifeq ($(OS),Windows_NT)
	$(CC) $(CFLAGS) main.o Linker.o ObjectModule.o -o linkador.exe
else
	$(CC) $(CFLAGS) main.o Linker.o ObjectModule.o -o linkador
endif

main.o: main.cpp Linker.o
	$(CC) $(CFLAGS) -c main.cpp

Linker.o: Linker.cpp Linker.hpp ObjectModule.o
	$(CC) $(CFLAGS) -c Linker.cpp Linker.hpp

ObjectModule.o: ObjectModule.cpp ObjectModule.hpp
	$(CC) $(CFLAGS) -c ObjectModule.cpp ObjectModule.hpp

clean:
	rm *.o  *.gch linkador*

remake:
	make clean
	make all
