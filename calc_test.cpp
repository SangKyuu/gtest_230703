// calc_test.cpp

extern "C" {
#include "calc.h"
}

#include <gtest/gtest.h>

TEST(CalcTest, Add)
{
    EXPECT_EQ(30, Add(10, 20));
}

TEST(CalcTest, Sub)
{
    EXPECT_EQ(-10, Sub(10, 20));
}

/*
$ g++ calc_test.cpp calc.o -I  ./googletest/googletest/include/ -L. -lgtest -pthread

*/
