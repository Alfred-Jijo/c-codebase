NAME = codebase
VERSION = 0.0.1
PREFIX ?= $(HOME)/.local

GCC ?= gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -Wno-unused-parameter -Wshadow -std=c99 

SRC = src/main.c
OBJ = $(SRC:%.c=%.o)
INCLUDE = Iinclude

all: clean $(NAME) run

$(NAME): $(OBJ)
	$(GCC) $(OBJ) -o $(NAME) $(CFLAGS) $(INCLUDE)

.c.o:
	$(GCC) -c $< -o $@ $(CFLAGS) $(INCLUDE)

run: $(NAME)
	./$(NAME)

clean:
	$(RM) $(OBJ)
	$(RM) $(NAME)

.PHONY: all clean
