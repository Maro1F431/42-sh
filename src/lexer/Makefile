CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -std=c99 -g
VPATH=tests

BIN=lexer
BIN_DEBUG=check

OBJS=helper.o main.o lexer.o token.o token_rec.o
OBJS_DEBUG=lexer.o functional.o helper.o token.o token_rec.o

all:$(BIN)
$(BIN):$(OBJS)
	$(CC) $^ -o $@ $(CFLAGS)

$(BIN_DEBUG):$(OBJS_DEBUG)
	$(CC) $^ -o $@ $(CFLAGS) -lcriterion
	./check

clean:
	$(RM) $(OBJS) $(BIN) $(OBJS_DEBUG) $(BIN_DEBUG)
