#!/bin/sh
g++ $1 -I./googletest/googletest/include -L. -lgtest -pthread -std=c++14 -fsanitize=leak
