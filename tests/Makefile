-include ../Makefile
.DEFAULT_GOAL := allLocal

PATH2SRC = ../src/
PATH2OBJ = ../obj/

# include any test.cc files here, and create an appropriate .yml workflow in the .github/workflow folder
TEST_SOURCES := pawnpush2test pawnpromotiontest pawncapturetest bishopmovestest knightmovetest rookmovestest invalidpostest kingcheckstest
TEST_TARGETS := $(patsubst %.cc,%,$(TEST_SOURCES))

allLocal: $(TEST_TARGETS)
	@./runTests.sh
	
%: %.cc $(OBJ)
	$(CC) -o $@ $< $(OBJ) $(LIB)

.PHONY: clean
clean:
	rm -f $(patsubst %.cc,%,$(TEST_SOURCES))
