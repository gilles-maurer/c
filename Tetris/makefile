all: main

main: main.o primlib.o functions.o piece_definition.o
	gcc -fsanitize=undefined -g $^ -o $@  -lSDL2_gfx `sdl2-config --libs` -lm

.c.o: 
	gcc -fsanitize=undefined -g -Wall -pedantic `sdl2-config --cflags` -c  $<

primlib.o: primlib.h

functions.o: primlib.h functions.h piece_definition.h

piece_definition.o: piece_definition.h

main.o: primlib.h functions.h piece_definition.h

clean:
	-rm primlib.o functions.o piece_definition.o main.o main
