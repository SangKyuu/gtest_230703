// 10_파라미터화테스트2.cpp
#include <string>
#include <iostream>

bool Process(const std::string& name, int age)
{
    // ...
    std::cout << name << ", " << age << std::endl;
    return false;
    // return true;
}

#include <gtest/gtest.h>

#if 0
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
#endif

#if 1
struct InputType {
    std::string name;
    int age;
};

// 사용자 정의 타입을 사용할 때는
// 테스트가 실패할 경우, 어떤 데이터를 가지고 있는 메모리를 덤프해서 보여줍니다.
// => 연산자 오버로딩을 제공해야 합니다.
std::ostream& operator<<(std::ostream& os, const InputType& data)
{
    return os << data.name << ", " << data.age;
}

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

    EXPECT_TRUE(Process(data.name, data.age));
}
#endif
