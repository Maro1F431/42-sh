CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -std=c99 -g
LDFLAGS= -lreadline
VPATH=tests

BIN=lexer
BIN_DEBUG=check

OBJS= main.o lexer.o token.o token_rec.o
OBJS_DEBUG=lexer.o functional.o token.o token_rec.o

all:$(BIN)
$(BIN):$(OBJS)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS) -fsanitize=address

$(BIN_DEBUG):$(OBJS_DEBUG)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS) -lcriterion
	./check

clean:
	$(RM) $(OBJS) $(BIN) $(OBJS_DEBUG) $(BIN_DEBUG)
