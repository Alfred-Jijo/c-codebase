NAME = codebase
VERSION = 0.0.4
PREFIX ?= $(HOME)/.local

GCC ?= gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -Wno-unused-parameter -Wshadow

SRC = lib/Allocator.c  src/main.c
OBJ = $(SRC:%.c=%.o)
INCLUDE = -Iinclude 

all: clean $(NAME) run

$(NAME): $(OBJ)
	$(GCC) $(OBJ) -o ./out/$(NAME) $(CFLAGS) $(INCLUDE)

.c.o:
	$(GCC) -c $< -o $@ $(CFLAGS) $(INCLUDE)

run: $(NAME)
	./out/$(NAME)

clean:
	$(RM) $(OBJ)
	$(RM) $(NAME)

.PHONY: all clean
