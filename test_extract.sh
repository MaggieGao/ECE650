#!/bin/bash

make clean
make all
cat ./test.in | ./a2-ece650
