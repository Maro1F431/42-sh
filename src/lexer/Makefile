C=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -std=c99 -g

BIN=lexer
OBJS=helper.o main.o lexer.o

all:$(BIN)

$(BIN):$(OBJS)

clean:
	$(RM) $(OBJS) $(BIN)
