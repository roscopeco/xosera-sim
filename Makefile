#
# Xosera Simulator
# 
# Copyright (c) 2024 The Really Old-School Company Limited
# 
# See LICENSE.md for legal jargon.
#

CFLAGS=$(shell pkg-config --cflags sdl2) -Iinclude -g
LDFLAGS=$(shell pkg-config --libs sdl2)

all: main

main: main.o xosera.o xo_scanout.o sdl_frontend.o

clean: 
	rm -rf *.o main

.PHONY: all clean
