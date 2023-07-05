// 20_행위기반검증.cpp
//  정의: SUT 내부에서 협력 객체(테스트 대역)를 대상으로 함수의 호출을 통해
//       정상 동작 여부를 검증합니다.
//   1) 함수 호출 여부
//   2) 함수 호출 횟수
//   3) 함수 호출 인자
//   4) 함수 호출 순서

class Person {
public:
    virtual ~Person() { }

    virtual void Go(int x, int y) = 0;
};

#include <gmock/gmock.h>

class MockPerson : public Person {
public:
    MOCK_METHOD(void, Go, (int x, int y), (override));
};

void UsePerson(Person* p)
{
    p->Go(10, 20);
}

// 1. 함수 호출 여부
//   EXPECT_CALL
TEST(PersonTest, Sample)
{
    MockPerson mock;

    // EXPECT_CALL(mock, Go);
    // 함수의 인자에 상관없이 호출 여부를 판단합니다.

    EXPECT_CALL(mock, Go(10, 20));
    // Go(10, 20) 함수의 호출 여부를 판단합니다.

    UsePerson(&mock);
}

// 2. 함수 호출 횟수
// * 인자의 매칭에 따라서 호출 횟수 판단이 달라집니다.
void UsePerson2(Person* p)
{
    p->Go(10, 20);
    p->Go(10, 20);

    p->Go(100, 20);
}

// EXPECT_CALL(...).Times(N)
// EXPECT_CALL(...).Times(Cardinality)

// Cardinality
// 1) AtLeast(N) => N번 이상
// 2) AtMost(N)  => N번 이하
// 3) Between(A, B) => A ~ B번

using testing::AtLeast;
using testing::AtMost;
using testing::Between;

TEST(PersonTest2, Sample)
{
    MockPerson mock;

    // EXPECT_CALL(mock, Go(10, 20));
    // 1번의 호출이 발생하는 것을 기대합니다.

    // EXPECT_CALL(mock, Go(10, 20)).Times(3);
    // EXPECT_CALL(mock, Go).Times(3);

    // EXPECT_CALL(mock, Go(10, 20)).Times(2);
    // EXPECT_CALL(mock, Go(100, 20));

    // 1) Go(10, 20)은 2번 이하 호출되어야 합니다.
    // EXPECT_CALL(mock, Go(10, 20)).Times(AtMost(2));
    // 2) Go(100, 20)은 1번 이상 호출되어야 합니다.
    // EXPECT_CALL(mock, Go(100, 20)).Times(AtLeast(1));

    // Go는 인자에 상관없이 1번에서 3번까지 호출되어야 합니다.
    EXPECT_CALL(mock, Go).Times(Between(1, 3));

    UsePerson2(&mock);
}

// 3. 함수 호출 인자
//  => Matcher

void UsePerson3(Person* p)
{
    p->Go(99, -20);
    p->Go(100, 120);
    p->Go(33, -25);
}

using testing::Eq;
using testing::Ge;
using testing::Gt;
using testing::Le;
using testing::Lt;

using testing::_;

using testing::AllOf; // &&
using testing::AnyOf; // ||
using testing::Matcher;

TEST(PersonTest3, Sample)
{
    MockPerson mock;

    // > Go의 첫번째 인자는 10이상이고,
    //       두번째 인자는 20인 형태로 3번 호출됩니다.
    // EXPECT_CALL(mock, Go(Ge(10), Eq(20))).Times(3);

    // > Go의 첫번째 인자는 아무값이 상관없고,
    //       두번째 인자는 30보다 작아야 합니다.
    // EXPECT_CALL(mock, Go(_, Lt(30))).Times(3);

    // EXPECT_CALL(mock, Go(_, _)).Times(3);
    // > EXPECT_CALL(mock, Go).Times(3);

    // 첫번째 인자: 10 < arg0 <= 100
    //           10 < arg0 && arg0 <= 100
    //           AllOf(Gt(10), Le(100))
    // Matcher<int> arg0 = AllOf(Gt(10), Le(100));
    auto arg0 = AllOf(Gt(10), Le(100));

    // 두번째 인자: arg1 < 0, arg1 > 100
    //           arg1 < 0 || arg1 > 100
    //           AnyOf(Lt(0), Gt(100))
    Matcher<int> arg1 = AnyOf(Lt(0), Gt(100));

    EXPECT_CALL(mock, Go(arg0, arg1)).Times(3);

    UsePerson3(&mock);
}
