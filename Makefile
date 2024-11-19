NAME = codebase
VERSION = 0.0.9
PREFIX ?= $(HOME)/.local

GCC ?= gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -Wno-unused-parameter -Wshadow

SRCLIB = lib/Allocator.c lib/DSA.c 
TESTLIB = lib/Allocator.c lib/unity.c

SRC = $(SRCLIB) src/main.c
OBJ = $(SRC:%.c=%.o)

TEST = $(TESTLIB) test/main_test.c
TEST_OBJ = $(TEST:%.c=%.o)

OUT = out/
INCLUDE = -Iinclude 

all: clean $(NAME) run

$(NAME): $(OBJ)
	$(GCC) $(OBJ) -o $(OUT)$(NAME) $(CFLAGS) $(INCLUDE)

.c.o:
	$(GCC) -c $< -o $@ $(CFLAGS) $(INCLUDE)

run: $(NAME)
	$(OUT)$(NAME)

test: $(TEST_OBJ) 
	$(GCC) $(TEST_OBJ) -o $(OUT)test $(CFLAGS) $(INCLUDE) -lm

run_test: test
	$(OUT)test

clean:
	$(RM) $(OBJ)
	$(RM) $(OUT)$(NAME)

clean_test:
	$(RM) $(TESTOBJ)
	$(RM) $(OUT)test

.PHONY: all clean test
