// 8_FriendTest.cpp

// User.h
#if 0
class User {
    int age = 0;

    int GetAge() const { return age; }

public:
    void foo() { age = 42; }
};
#endif

// #define private public
// #define class struct
#include "User.h"
// #undef private
// #undef class
// > 절대 좋은 방법이 아닙니다.
#include <gtest/gtest.h>

// * 제품 코드는 테스트를 작성하는 비용이 최소화되어야 합니다.
// * private 메소드
//  => public 메소드를 검증할 때, 자연스럽게 private 메소드도
//     호출되어서 검증되어야 합니다.
//  => private 메소드는 public 메소드의 가독성을 높이기 위해
//     사용해야 합니다.
//   "Clean Code"

TEST(UserTest, foo)
{
    User user;

    user.foo();

    // EXPECT_EQ(user.age, 42);
    EXPECT_EQ(user.GetAge(), 42);
}
