CC = g++
CFLAGS = -O2

all: main.o Linker.o ObjectModule.o
	$(CC) $(CFLAGS) main.o Linker.o ObjectModule.o -o sb.exe

main.o: main.cpp Linker.o
	$(CC) $(CFLAGS) -c main.cpp

Linker.o: Linker.cpp Linker.hpp ObjectModule.o
	$(CC) $(CFLAGS) -c Linker.cpp Linker.hpp

ObjectModule.o: ObjectModule.cpp ObjectModule.hpp
	$(CC) $(CFLAGS) -c ObjectModule.cpp ObjectModule.hpp

clean:
	rm *.o  *.gch sb.exe

remake:
	make clean
	make all
