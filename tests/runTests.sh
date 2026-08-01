#!/bin/bash

TEST_SOURCES="pawnpush2test pawnpromotiontest pawncapturetest bishopmovestest knightmovetest rookmovestest invalidpostest kingcheckstest enpassantcheckmatetest"

for test_source in $TEST_SOURCES; do
    ./"$test_source"
done
