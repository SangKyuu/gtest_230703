// 1_시작.cpp
#include <gtest/gtest.h>

// google test main 함수
// > gtest_main.cc 라는 소스코드를 제공합니다.
// - 라이브러리에 빌드해서 포함시키면, main을 매번 작성할 필요가 없습니다.
#if 1
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif

// $ g++ 1_시작.cpp -I./googletest/googletest/include -L. -lgtest -pthread -std=c++14
// $ ./a.out
