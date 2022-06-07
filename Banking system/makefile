# List your *.h files (if you do not have them in your project then leave the variable "headers" empty):
headers = functions.h utils.h

# List your *.c files:
sources = functions.c utils.c main.c

# Specify name of your program:
executable = myprogram

$(executable): $(headers) $(sources)
	gcc -g -Wall -pedantic $(sources) -o $(executable)

.PHONY: clean
clean:
	rm $(executable)


