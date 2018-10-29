CC=gcc
INCLUDE=../qemu
FLAGS=-Wall -rdynamic

all: main

main: main.o
	$(CC) main.o -ldl -o main

main.o: main.c
	$(CC) $(FLAGS) -I$(INCLUDE) -c main.c -o main.o

clean:
	rm -rf main *.o
