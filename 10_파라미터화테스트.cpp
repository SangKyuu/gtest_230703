// 10_파라미터화테스트.cpp

bool IsPrime(int value)
{
    for (int i = 2; i < value; ++i) {
        if (value % i == 0) {
            return false;
        }
    }

    return true;
}

// 입력 데이터를 바꿔가며, 반복 검사하는 데이터 중심의 테스트에서
// 테스트 코드 중복의 문제를 해결할 수 있는 기능을 제공하고 있습니다.
// => Parameterized Test(파라미터화 테스트)
#include <gtest/gtest.h>

// 1. 명시적인 테스트 스위트 클래스가 필요합니다.
//          기존) class PrimeTest : public testing::Test {};
// 파라미터화 테스트) class PrimeTest : public testing::TestWithParam<데이터타입> {};
class PrimeTest : public testing::TestWithParam<int> {
};

// 2. 데이터 셋을 정의해야 합니다.
// => INSTANTIATE_TEST_SUITE_P(데이터 셋 이름(prefix), 테스트 스위트 클래스, 데이터셋)
INSTANTIATE_TEST_SUITE_P(PrimeValues, PrimeTest,
    testing::Values(2, 3, 5, 7, 11, 13, 17, 23));

// 3. 데이터셋을 활용하는 다양한 테스트케이스를 작성하면 됩니다.
//  -   TEST: 암묵적인 테스트 스위트 클래스
//  - TEST_F: 명시적인 테스트 스위트 클래스
//  - TEST_P: 파라미터화 테스트의 테스트케이스를 만드는 방법
TEST_P(PrimeTest, IsPrime)
{
    // GetParam(): 데이터 셋의 데이터를 얻어올 수 있습니다.
    EXPECT_TRUE(IsPrime(GetParam()));
}

#if 0
TEST(PrimeTest, IsPrime)
{
    EXPECT_TRUE(IsPrime(2));
    EXPECT_TRUE(IsPrime(3));
    EXPECT_TRUE(IsPrime(5));
    EXPECT_TRUE(IsPrime(7));
    // ...
}

TEST(PrimeTest, IsPrime2)
{
    int data[] = { 2, 3, 7, 11, 13, 17, 23 };
    for (auto e : data) {
        EXPECT_TRUE(IsPrime(e));
    }
}
#endif
