// 6_GoogleTest2.cpp
#include <gtest/gtest.h>

// 6. 테스트 필터
// > 원하는 테스트만 선택적으로 수행할 수 있습니다.
// => 테스트 이름을 잘 구성하는 것이 효과적입니다.

// $ ./a.out --gtest_filter=ImageTest.foo

// ImageTest.foo
TEST(ImageTest, foo) { }
// ImageTest.goo
TEST(ImageTest, goo) { }
// ImageTest.hoo
TEST(ImageTest, hoo) { }

// // ImageProcessorTest.foo
TEST(ImageProcessorTest, foo) { }
TEST(ImageProcessorTest, goo) { }
TEST(ImageProcessorTest, hoo) { }
