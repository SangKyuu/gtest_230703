// 10_파라미터화테스트4.cpp
#include <gtest/gtest.h>

// 데이터 셋을 정의하는 함수
//  1. testing::Values
//  2. testing::ValuesIn
//  3. testing::Combine
//  4. testing::Range
//    - testing::Range(1, 100) => 1, 2, ... 99
//    - testing::Range(1, 100, 3) => 1, 4, ... 97

class SampleTest : public testing::TestWithParam<int> {
};

// 1 ~ 99
INSTANTIATE_TEST_SUITE_P(SampleValues, SampleTest,
    testing::Range(1, 100, 3));

TEST_P(SampleTest, Sample)
{
    std::cout << GetParam() << std::endl;
}
