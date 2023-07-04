#!/bin/sh
g++ $1 -I./googletest/googletest/include \
-I./googletest/googlemock/include \
-L. -lgtest \
-pthread -std=c++14
