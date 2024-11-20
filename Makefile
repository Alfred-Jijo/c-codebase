NAME = codebase
VERSION = 0.0.9
PREFIX ?= $(HOME)/.local

CC ?= gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -Wno-unused-parameter -Wshadow

SRCLIB = lib/Allocator.c lib/DSA.c 
TESTLIB = $(SRCLIB) lib/unity/unity.c

SRC = $(SRCLIB) src/main.c
OBJ = $(SRC:%.c=%.o)

TEST = $(TESTLIB) test/main_test.c
TEST_OBJ = $(TEST:%.c=%.o)

OUT = out/
INCLUDE = -Iinclude -Ilib/unity/

all: clean $(NAME) run
test: clean_test $(NAME)_test run_test

.c.o:
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(OUT)$(NAME) $(CFLAGS) $(INCLUDE)

run: $(NAME)
	clear
	@echo "$(NAME)"
	@echo "=========="
	$(OUT)$(NAME)

clean: clean_test
	$(RM) $(OBJ)
	$(RM) $(OUT)$(NAME)

$(NAME)_test: $(TEST_OBJ) 
	$(CC) $(TEST_OBJ) -o $(OUT)test $(CFLAGS) $(INCLUDE)

run_test: 
	clear
	@echo "$(NAME)_test"
	@echo "=========="
	$(OUT)test

clean_test:
	$(RM) $(TEST_OBJ)
	$(RM) $(OUT)test

.PHONY: all clean test
