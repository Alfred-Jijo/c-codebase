NAME = codebase
VERSION = 0.0.3
PREFIX ?= $(HOME)/.local

GCC ?= gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -Wno-unused-parameter -Wshadow

SRC = src/Allocator.c src/main.c

OBJ = $(SRC:%.c=%.o)

all: clean $(NAME) run

$(NAME): $(OBJ)
	$(GCC) $(OBJ) -o ./out/$(NAME) $(CFLAGS)

.c.o:
	$(GCC) -c $< -o $@ $(CFLAGS)

run: $(NAME)
	./out/$(NAME)

clean:
	$(RM) $(OBJ)
	$(RM) $(NAME)

.PHONY: all clean
