
CC=g++
LIBS=-lc -lstdc++ -ldl -lpthread

SRC=main.cpp
TARGET=gvm1.bin

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $< -o $@ $(LIBS)

clean:
	rm -f $(TARGET)
