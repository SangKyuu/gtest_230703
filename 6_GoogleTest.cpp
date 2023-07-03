// 6_GoogleTest.cpp
// 1) Fixture
// 2) Assertion
#include <gtest/gtest.h>

int foo() { return 4; }
int goo() { return 10; }

// 1. ASSERT_XXX
// - 단언문이 실패할 경우, 이후의 코드는 수행되지 않습니다.
//   하나의 테스트 케이스 안에 여러 개의 단언문이 존재할 경우
//   이후의 단언문을 검증을 수행하지 않는 문제가 발생합니다.
//    "죽은 단언문"
//   => xUnit Test Pattern에서는 하나의 테스트케이스 안에
//      여러개의 단언문을 두지말자.
//   => Google Test는 새로운 단언문을 제공합니다.
//      EXPECT_XXX
TEST(SampleTest, Sample1)
{
    // ...
    ASSERT_EQ(foo(), 42);
    ASSERT_EQ(goo(), 100);
}

// EXPECT_XXX
// => 단언문이 실패할 경우, 테스트의 결과는 실패입니다.
//    이후의 코드를 계속 수행합니다.
//    "죽은 단언문" 해결!
TEST(SampleTest, Sample2)
{
    // ...
    EXPECT_EQ(foo(), 42);
    EXPECT_EQ(goo(), 100);
}
