// 9_테스트전용하위클래스.cpp

class User {
    int age = 10;

protected:
    int GetAge() const { return age; }

public:
    void foo() { age = 42; }
};

// 문제점: 테스트를 통해 확인하고자 하는 상태가 protected 입니다.
// 해결 방법
//  => 테스트 전용 하위 클래스 패턴(Test Specific Subclass Pattern)

#include <gtest/gtest.h>

class TestUser : public User {
public:
    // int GetAge() const { return User::GetAge(); }
    using User::GetAge;
    // 위의 문법을 통해 부모의 protected를 public으로 변경할 수 있습니다.
};

TEST(UserTest, foo)
{
    TestUser user;
    user.foo();

    EXPECT_EQ(user.GetAge(), 42);
}

#if 0
TEST(UserTest, foo)
{
    User user;
    user.foo();

    EXPECT_EQ(user.GetAge(), 42);
}
#endif
