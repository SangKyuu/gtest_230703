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

TEST(UserTest, foo)
{
    User user;

    user.foo();

    // EXPECT_EQ(user.age, 42);
    EXPECT_EQ(user.GetAge(), 42);
}
