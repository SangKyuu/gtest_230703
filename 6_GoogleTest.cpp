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

class User {
    std::string name = "Tom";

public:
    std::string GetName() const { return name; }
};

User* GetUser() { return nullptr; }

TEST(SampleTest, Sample3)
{
    User* user = GetUser();

    // EXPECT_NE(user, nullptr);
    ASSERT_NE(user, nullptr); // 의도적으로 이후의 단언문을 수행하지 않습니다.
    EXPECT_EQ(user->GetName(), "Tom");
}

// 2. C 문자열 비교 단언문
//  => char[], const char*
//   EXPECT_STREQ / STRNE
//   EXPECT_STRCASEEQ / STRCASENE => 대소문자 무시
TEST(SampleTest2, Sample1)
{
    std::string s1 = "hello";
    std::string s2 = "hello";
    EXPECT_EQ(s1, s2);

    const char* s3 = "hello";
    char s4[] = "Hello";
    // EXPECT_EQ(s3, s4); // s3 == s4
    // EXPECT_STREQ(s3, s4);
    EXPECT_STRCASEEQ(s3, s4);
}

// 3. 부동 소수점 비교 단언문
// => EXPECT_FLOAT_EQ / NE
//    EXPECT_DOUBLE_EQ / NE

// => 오차 범위를 직접 지정하고 싶다면,
//    EXPECT_NEAR
TEST(SampleTest3, Sample1)
{
    double a = 0.7;
    double b = 0.1 * 7.1;

    // EXPECT_EQ(a, b);
    EXPECT_FLOAT_EQ(a, b);
    EXPECT_NEAR(a, b, 0.00000001);
}

void OpenFile(const std::string& filename)
{
    if (filename.empty()) {
        throw std::invalid_argument("invalid filename");
        // throw 1;
    }

    // ...
}

// 잘못된 파일명을 전달하였을 경우, std::invalid_argument 예외가
// 발생하는지 여부를 검증하고 싶다.
TEST(SampleTest4, OpenFile)
{
    std::string emptyFileName = "";

    try {
        OpenFile(emptyFileName);
        FAIL() << "기대한 예외가 발생하지 않음";
    } catch (std::invalid_argument& e) {
        SUCCEED();
    } catch (...) {
        FAIL() << "다른 종류의 예외가 발생함.";
    }
}

// 4. 예외 검증 단언문을 제공합니다.
//  => EXPECT_THROW: 기대한 예외가 발생하는지 여부를 검증합니다.
//     EXPECT_NO_THROW: 예외가 발생하지 않음을 검증합니다.
//     EXPECT_ANY_THROW: 예외가 발생하는지 여부를 검증합니다.

TEST(SampleTest4, OpenFile2)
{
    std::string emptyFileName = "";

    EXPECT_THROW(OpenFile(emptyFileName), std::invalid_argument);
}
