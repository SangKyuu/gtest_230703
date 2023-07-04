// 10_파라미터화테스트2.cpp
#include <string>
#include <iostream>

bool Process(const std::string& name, int age)
{
    // ...
    std::cout << name << ", " << age << std::endl;
    return false;
}

#include <gtest/gtest.h>

using InputType = std::tuple<std::string, int>;

class ProcessTest : public testing::TestWithParam<InputType> {
};

INSTANTIATE_TEST_SUITE_P(ProcessValues, ProcessTest,
    testing::Values(
        InputType { "Tom", 42 },
        InputType { "Bob", 100 },
        InputType { "Alice", 16 }));

TEST_P(ProcessTest, Process)
{
    const InputType& data = GetParam();

    EXPECT_TRUE(Process(std::get<0>(data), std::get<1>(data)));
}
