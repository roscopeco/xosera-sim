#
# Xosera Simulator
# 
# Copyright (c) 2024 The Really Old-School Company Limited
# 
# See LICENSE.md for legal jargon.
#

CFLAGS=$(shell pkg-config --cflags sdl2) -Iinclude -g -Wall -Wextra -Werror -Wpedantic
LDFLAGS=$(shell pkg-config --libs sdl2)

.PHONY: all test clean

all: check main

check: test

test:
	$(MAKE) -C test test
	
main: main.o xo_init.o xo_scanout.o xo_copper.o sdl_frontend.o

clean: 
	rm -rf *.o main
	$(MAKE) -C test clean

.PHONY: all clean
