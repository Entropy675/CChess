-include ../Makefile
.DEFAULT_GOAL := all

PATH2SRC = ../src/
PATH2OBJ = ../obj/

TEST_SOURCES := pawnpush2test.cc
TEST_TARGETS := $(patsubst %.cc,%,$(TEST_SOURCES))

all: $(TEST_TARGETS)

%: %.cc $(OBJ)
	$(CC) -o $@ $< $(OBJ) $(LIB)

.PHONY: clean
clean:
	rm -f $(TEST_TARGETS)
