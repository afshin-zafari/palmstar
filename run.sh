#!/bin/bash
LOG_FILE="./out/log.txt"
make
echo
echo "Start running the program."
echo
./out/palmmain &> $LOG_FILE

echo
echo "program finished with output in '$LOG_FILE'"
echo
