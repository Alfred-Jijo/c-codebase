NAME = codebase
VERSION = 0.0.1
PREFIX ?= $(HOME)/.local

GCC ?= gcc
CFLAGS =  -std=c99 -Wall -Wextra -Werror -pedantic -Wno-unused-parameter -Wshadow

SRC = src/main.c
OBJ = $(SRC:%.c=%.o)

all: clean $(NAME) run

$(NAME): $(OBJ)
	$(GCC) $(OBJ) -o $(NAME) $(CFLAGS)

.c.o:
	$(GCC) -c $< -o $@ $(CFLAGS)

run: $(NAME)
	./$(NAME)

clean:
	$(RM) $(OBJ)
	$(RM) $(NAME)

.PHONY: all clean
