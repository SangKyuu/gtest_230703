// calc_test.cpp

#if 1
extern "C" {
#include "calc.h"
}
#endif

// #include "calc.c"

#include <gtest/gtest.h>

TEST(CalcTest, Add)
{
    foo();
    EXPECT_EQ(30, Add(10, 20));
}

TEST(CalcTest, Sub)
{
    EXPECT_EQ(-10, Sub(10, 20));
}

/*
$ g++ calc_test.cpp calc.o -I  ./googletest/googletest/include/ -L. -lgtest -pthread

*/
