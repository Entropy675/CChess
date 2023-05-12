-include ../Makefile
.DEFAULT_GOAL := all

PATH2SRC = ../src/
PATH2OBJ = ../obj/

# include any test.cc files here, and create an appropriate .yml workflow in the .github/workflow folder
TEST_SOURCES := pawnpush2test.cc pawnpromotiontest.cc pawncapturetest.cc bishopmovestest.cc knightmovetest.cc
TEST_TARGETS := $(patsubst %.cc,%,$(TEST_SOURCES))

all: $(TEST_TARGETS)

%: %.cc $(OBJ)
	$(CC) -o $@ $< $(OBJ) $(LIB)

.PHONY: clean
clean:
	rm -f $(TEST_TARGETS)
