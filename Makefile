OS := $(shell uname)

ifeq ($(OS), Linux)
    RM = rm -rf
    EXE_EXT =
else ifeq ($(OS), Darwin) # macOS
    RM = rm -rf
    EXE_EXT =
else ifeq ($(OS), Windows_NT)
    RM = del /Q
    EXE_EXT = .exe
endif


NAME = codebase$(EXE_EXT)
VERSION = 0.1.1
PREFIX ?= $(HOME)/.local

CC := $(shell which gcc || which clang || echo "gcc")
CXX := $(shell which g++ || which clang++ || echo "g++")

CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -Wno-unused-parameter -Wshadow

ifeq ($(OS), Linux)
    CFLAGS += -DLINUX
else ifeq ($(OS), Darwin)
    CFLAGS += -DMACOS
else ifeq ($(OS), Windows_NT)
    CFLAGS += -DWINDOWS
endif

SRCLIB = lib/arena.c lib/dsa.c lib/gpa.c
TESTLIB = $(SRCLIB) lib/unity/unity.c

SRC = $(SRCLIB) src/main.c
OBJ = $(SRC:%.c=%.o)

TEST = $(TESTLIB) test/main_test.c
TEST_OBJ = $(TEST:%.c=%.o)

OUT = out/
INCLUDE = -Iinclude -Ilib/unity/

all: $(NAME) run clean
test: $(NAME)_test run_test clean_test

.c.o:
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(OUT)$(NAME) $(CFLAGS) $(INCLUDE)

run: $(NAME)
	clear
	@echo ""
	@echo "=====$(NAME)====="
	$(OUT)$(NAME)

clean: clean_test
	$(RM) $(OBJ)
	$(RM) $(OUT)$(NAME)
	@echo ""

$(NAME)_test: $(TEST_OBJ) 
	$(CC) $(TEST_OBJ) -o $(OUT)test $(CFLAGS) $(INCLUDE)

run_test: 
	clear
	@echo "$(NAME)_test"
	@echo "=========="
	$(OUT)test

clean_test:
	@echo ""
	@echo ""
	@echo "=====Cleaning====="
	$(RM) $(TEST_OBJ)
	$(RM) $(OUT)test
	@echo ""

.PHONY: all clean test
