-include ../Makefile
.DEFAULT_GOAL := allLocal

PATH2SRC = ../src/
PATH2OBJ = ../obj/

# Every *test.cc here IS a test entry point -- the filename is the sole
# declaration, no list to maintain anywhere.
TEST_SOURCES := $(wildcard *test.cc)
TEST_TARGETS := $(patsubst %.cc,%,$(TEST_SOURCES))

# The engine is a dependency. Build/update it via the ROOT makefile (which owns
# the object rules and its own paths) before building any test. Two phases: the
# recursion below finishes -- creating ../obj/*.o -- before the second make even
# parses $(OBJ) as prerequisites, so there's no "no rule for ../obj/X.o".
allLocal:
	@$(MAKE) --no-print-directory -C ..
	@$(MAKE) --no-print-directory runTests

runTests: $(TEST_TARGETS)
	@fail=0; \
	for t in $(TEST_TARGETS); do \
		printf '\n=== %s ===\n' "$$t"; \
		./$$t; \
		rc=$$?; \
		if [ $$rc -gt 0 ]; then echo "FAIL: $$t (exit $$rc)"; fail=1; fi; \
	done; \
	echo; \
	if [ $$fail -ne 0 ]; then echo "SOME TESTS FAILED"; exit 1; fi; \
	echo "ALL TESTS PASSED"

# By the time runTests builds these, the recursion has ensured $(OBJ) exist.
%: %.cc $(OBJ)
	$(CC) -o $@ $< $(OBJ) $(LIB)

.PHONY: clean allLocal runTests
clean:
	rm -f $(TEST_TARGETS)
