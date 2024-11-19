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
test: clean_test build_test run_test

.c.o:
	$(GCC) -c $< -o $@ $(CFLAGS) $(INCLUDE)

$(NAME): $(OBJ)
	$(GCC) $(OBJ) -o $(OUT)$(NAME) $(CFLAGS) $(INCLUDE)

run: $(NAME)
	$(OUT)$(NAME)

clean:
	$(RM) $(OBJ)
	$(RM) $(OUT)$(NAME)

build_test: $(TEST_OBJ) 
	$(GCC) $(TEST_OBJ) -o $(OUT)test $(CFLAGS) $(INCLUDE) -lm

run_test: 
	$(OUT)test

clean_test:
	$(RM) $(TEST_OBJ)
	$(RM) $(OUT)test

.PHONY: all clean test
