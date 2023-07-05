// 20_행위기반검증2.cpp
class Dog {
public:
    virtual ~Dog() { }

    virtual void First() = 0;
    virtual void Second() = 0;
    virtual void Third() = 0;
    virtual void Fourth() = 0;
};

#include <gmock/gmock.h>

class MockDog : public Dog {
public:
    MOCK_METHOD(void, First, (), (override));
    MOCK_METHOD(void, Second, (), (override));
    MOCK_METHOD(void, Third, (), (override));
    MOCK_METHOD(void, Fourth, (), (override));
};

void Process(Dog* p)
{
    p->First();
    p->Second();
    p->Third();
    p->Fourth();
}

// First -> Second -> Third -> Fourth
// => testing::InSequence
using testing::InSequence;
TEST(DogTest, Sample)
{
    InSequence seq; // 호출 순서를 검증합니다.
    MockDog mock;

    EXPECT_CALL(mock, First);
    EXPECT_CALL(mock, Second);
    EXPECT_CALL(mock, Third);
    EXPECT_CALL(mock, Fourth);

    Process(&mock);
}

void Process2(Dog* p)
{
    p->First();

    p->Third();
    p->Fourth();

    p->Second();
}

// 함수의 순서 하나의 흐름 => testing::InSequence
// 함수의 2개 이상의 흐름 => testing::Sequence
//   EXPECT_CALL(..).InSequence()

// First -------> Second                  // seq1
//       |
//       -------> Third ------> Fourth    // seq2
TEST(DogTest, Sample2)
{
    testing::Sequence seq1, seq2;
    MockDog mock;

    EXPECT_CALL(mock, First).InSequence(seq1, seq2);
    EXPECT_CALL(mock, Second).InSequence(seq1);
    EXPECT_CALL(mock, Third).InSequence(seq2);
    EXPECT_CALL(mock, Fourth).InSequence(seq2);

    Process2(&mock);
}
