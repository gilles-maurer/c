all: main

main: main.o primlib.o functions.o
	gcc -g $^ -o $@  -lSDL2_gfx `sdl2-config --libs` -lm

.c.o: 
	gcc -g -Wall -pedantic `sdl2-config --cflags` -c  $<

primlib.o: primlib.c primlib.h

functions.o: functions.c functions.h

main.o: main.c primlib.h functions.h

clean:
	-rm primlib.o functions.o main.o main
