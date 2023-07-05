// 21_Hamcrest.cpp
// => 비교 표현의 확장 라이브러리
//  : Google Mock을 통해서 Matcher를 이용해 행위 기반 검증에서
//    인자를 검증하는 목적으로 사용할 수 있습니다.

#include <gmock/gmock.h>
// 상태 기반 검증에서 다양한 Matcher를 활용할 수 있습니다.
// => 단언문
//     ASSERT_THAT
//     EXPECT_THAT

std::string GetName() { return "Hello World"; }

using testing::AllOf;
using testing::ElementsAre;
using testing::EndsWith;
using testing::Eq;
using testing::Ge;
using testing::Gt;
using testing::Le;
using testing::Lt;
using testing::Ne;
using testing::StartsWith;

std::vector<int> GetData() { return { 1, 10, 5 }; }

// EXPECT_THAT(value, matcher)
// ASSERT_THAT(value, matcher)
TEST(SampleTest, GetName)
{
    // GetName 함수의 결과의 문자열이 Hello로 시작하고, World로 끝나는지 검증하고 싶습니다.
    EXPECT_THAT(GetName(), StartsWith("Hello")) << "이름을 요청하였을 때";
    EXPECT_THAT(GetName(), AllOf(StartsWith("Hello"), EndsWith("World")));

    EXPECT_THAT(GetData(), ElementsAre(Lt(10), Ge(1), Eq(5)));
}
