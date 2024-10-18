CFLAGS=$(shell pkg-config --cflags sdl2) -Iinclude -g
LDFLAGS=$(shell pkg-config --libs sdl2)

all: main

main: main.o

clean: 
	rm -rf *.o main

.PHONY: all clean
