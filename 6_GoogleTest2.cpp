// 6_GoogleTest2.cpp
#include <gtest/gtest.h>

// 6. 테스트 필터
// > 원하는 테스트만 선택적으로 수행할 수 있습니다.
// => 테스트 이름을 잘 구성하는 것이 효과적입니다.

// $ ./a.out --gtest_filter=ImageTest.foo
// $ ./a.out --gtest_filter=ImageTest.foo:ImageProcessorTest.goo
// $ ./a.out --gtest_filter=*.foo
// $ ./a.out --gtest_filter=Image*.goo
// $ ./a.out --gtest_filter=Image*.*:-*.goo

// ImageTest.foo
TEST(ImageTest, foo) { }
// ImageTest.goo
TEST(ImageTest, goo) { }
// ImageTest.hoo
TEST(ImageTest, hoo) { }

// ImageProcessorTest.foo
TEST(ImageProcessorTest, foo) { }
TEST(ImageProcessorTest, goo) { }
TEST(ImageProcessorTest, hoo) { }

// 7. 반복 테스트 / 순서 무작위
// $ ./a.out --gtest_repeat=10 --gtest_shuffle

// 테스트를 반복적으로 수행하다가, 테스트가 실패할 경우, 테스트를 강제로
// 종료할 수 있습니다.
// $ ./a.out --gtest_repeat=10 --gtest_shuffle --gtest_break_on_failure

// 테스트가 반복적으로 수행되어도, 테스트가 어떤 순서로 수행되어도
// 동일한 결과가 나올 수 있도록 만들어주어야 합니다.
int cnt = 0;
int GetCount() { return ++cnt; }

TEST(SampleTest, Sample1)
{
    EXPECT_EQ(1, GetCount());
}

TEST(SampleTest, Sample2)
{
    EXPECT_EQ(2, GetCount());
    FAIL() << "실패!";
}

TEST(SampleTest, Sample3)
{
    cnt = 0;
}

// 8. 테스트 결과 포맷터(Test Result Formatter)
// => 테스트의 결과를 XML로 export 할 수 있습니다.
// $ ./a.out --gtest_output=xml

// => 1.10 이후로 JSON 형식을 지원합니다.
// $ ./a.out --gtest_output=json

// C/C++ 커버리지
// => gcov(무료)
//    bullseye(유료) - https://www.bullseye.com/
