CC=gcc
INCLUDE=-I../qemu
CFLAGS=-Wall
LDFLAGS=

ifeq ($(shell uname), Linux)
	LDFLAGS=-ldl
else
	LDFLAGS=-L${INSTALL_PATH}/mingw/lib -ldl -lpsapi
	CC=x86_64-w64-mingw32-gcc
	INCLUDE+= -I${INSTALL_PATH}/mingw/include
endif

all: main

main: main.o
	$(CC) main.o $(LDFLAGS) -o main

main.o: main.c
	$(CC) $(CFLAGS) $(INCLUDE) -c main.c -o main.o

clean:
	rm -rf main *.o
