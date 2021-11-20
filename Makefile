# Makefile 

# target: dependencies
#	action 

# -c 	code to object file (.o), Compile and assemble, but do not link.
# -o	Place the output into <file>


GDB = -g
THREADING = -pthread
INCLUDES = -I ./include
OBJECTS = ./build/genetic.o ./build/dynamic.o

all: ${OBJECTS} ./src/main.cpp
	g++ ${GDB} ${INCLUDES} ${THREADING} ./src/main.cpp ${OBJECTS} -o ./bin/main

./build/genetic.o: ./src/genetic.cpp ./include/genetic.h ./include/loot.h 
	g++ ${GDB} ${INCLUDES} ./src/genetic.cpp -c -o ./build/genetic.o

./build/dynamic.o: ./src/dynamic.cpp ./include/dynamic.h ./include/loot.h 
	g++ ${GDB} ${INCLUDES} ./src/dynamic.cpp -c -o ./build/dynamic.o


clean:
	rm -f build/*.o bin/main

run: 
	bin/main

debug:
	gdb -tui bin/main
	
