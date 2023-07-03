// 1_시작.cpp
#include <gtest/gtest.h>

// google test main 함수
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// $ g++ 1_시작.cpp -I./googletest/googletest/include -L. -lgtest -pthread
// $ ./a.out