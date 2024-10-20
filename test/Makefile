CFLAGS=-Iinclude -I../include -g -Wall -Wextra -Werror -Wpedantic
LDFLAGS=

TEST_BINARIES=$(patsubst test_%.c,test_%,$(wildcard test_*.c))

.PHONY: check all clean __RUN_test_%

check: test

test: all $(patsubst test_%,__RUN_test_%,$(TEST_BINARIES))

all: $(TEST_BINARIES)

clean: 
	$(RM) $(TEST_BINARIES) *.o

sut_%.o: ../%.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

test_%: unity.o sut_xo_init.o sut_%.o test_%.o
	$(CC) $(LDFLAGS) -o $@ $^

__RUN_test_%: test_%
	./$<
