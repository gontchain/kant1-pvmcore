
CC=g++
CFLAGS=-Wno-write-strings
LIBS=-lc -lstdc++ -ldl -lpthread

SRC=main.cpp
TARGET=gvm1.bin

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $< $(CFLAGS) -o $@ $(LIBS)

clean:
	rm -f $(TARGET)
