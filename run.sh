#!/bin/bash
LOG_FILE="./out/log.txt"
TEST_RESULT="./out/test_result.txt"
make
echo
echo "Start running the program."
echo
./out/palmmain &> $LOG_FILE

echo
echo "program finished with output in '$LOG_FILE'"
echo

grep "Test Result" $LOG_FILE > $TEST_RESULT
cat $TEST_RESULT

grep "PROFILING" $LOG_FILE 