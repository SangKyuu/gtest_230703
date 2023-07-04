#ifndef USER_H
#define USER_H

// FRIEND_TEST
// => friend로 선언된 클래스가 private에 접근할 수 있습니다.
#include <gtest/gtest.h>
// FRIEND_TEST를 사용하기 위해서는,
// 제품 코드에 Google Test 의존성이 발생합니다.

class User {
    int age = 0;

    int GetAge() const { return age; }

public:
    void foo() { age = 42; }

    FRIEND_TEST(UserTest, foo);
};

#endif
