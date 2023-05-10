-include ../Makefile
.DEFAULT_GOAL := test

PATH2SRC = ../src/
PATH2OBJ = ../obj/
PATH2TESTS = tests/
	
test: $(OBJ)
	g++ -o test pawnpush2test.cc $(OBJ) $(LIB)

clean:
	rm -f test
	