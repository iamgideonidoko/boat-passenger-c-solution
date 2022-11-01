CC=gcc

default: program

main=src/main.c

font=src/boat.c

options=-lpthread

program:
	$(CC) $(font) $(main) $(options) -o main.o
	./main.o # running

clean:
	rm -f main.o