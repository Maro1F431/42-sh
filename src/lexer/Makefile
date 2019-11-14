CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -std=c99 -g
VPATH=tests

BIN=lexer
BIN_DEBUG=check

OBJS=helper.o main.o lexer.o
OBJS_DEBUG=lexer.o functional.o helper.o

all:$(BIN)
$(BIN):$(OBJS)

$(BIN_DEBUG):$(OBJS_DEBUG)
	$(CC) $^ -o $@ $(CFLAGS) -lcriterion

clean:
	$(RM) $(OBJS) $(BIN) $(OBJS_DEBUG) $(BIN_DEBUG)
