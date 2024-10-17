CFLAGS=-Iinclude -I/opt/homebrew/include -g
LDFLAGS=-L/opt/homebrew/lib -lSDL2 -g

all: main

main: main.o

clean: 
	rm -rf *.o main

.PHONY: all clean
