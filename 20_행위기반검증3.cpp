// 20_행위기반검증3.cpp
#include <iostream>

class Calc {
public:
    virtual ~Calc() { }

    virtual int Add(int a, int b) { return a + b; }
    virtual int Sub(int a, int b) { return a - b; }
};

void Process(Calc* p)
{
    if (p->Add(10, 20) == 30) {
        int result = p->Sub(100, 50);
        std::cout << "result: " << result << std::endl;
    }
}

//----
#include <gmock/gmock.h>

class MockCalc : public Calc {
public:
    MOCK_METHOD(int, Add, (int a, int b), (override));
    MOCK_METHOD(int, Sub, (int a, int b), (override));

    // 부모의 기능을 이용하기 위해서는 별도의 함수를 제공해야 합니다.
    int AddImpl(int a, int b) { return Calc::Add(a, b); }
    int SubImpl(int a, int b) { return Calc::Sub(a, b); }
};

// Google Mock은 MOCK_METHOD한 메소드의 행위 기반 검증 뿐 아니라,
// 결과를 제어하는 기능을 제공하고 있습니다.
// => Delegating
//  : ON_CALL
//   -> Test Stub / Fake Object

//  : EXPECT_CALL
//    을 이용해서 delegating을 수행할 수 있습니다.
//     .WillOnce       => 한번의 결과 제어
//     .WillRepeatedly => 연속적인 결과 제어

//    * 주의사항: 함수 호출 횟수 판단에 영향을 줍니다.
//    => .WillOnce 갯수 => Times(N)
//       .WillRepeatedly => AtLeast

//   - EXPECT_CALL(..)               => Times(1)

//   - EXPECT_CALL(..)
//      .WillOnce(Return(30))        => Times(1)

//   - EXPECT_CALL(..)               => Times(2)
//      .WillOnce(Return(30))
//      .WillOnce(Return(30))

//   - EXPECT_CALL(..)               => Times(AtLeast(2)) ; 2번 이상
//      .WillOnce(Return(30))
//      .WillOnce(Return(30))
//      .WillRepeatedly(Return(42)); => AtLeast

//  -  EXPECT_CALL(mock, Add(10, 20)) => Times(AtLeast(0))
//      .WillRepeatedly(Return(42));
//     => 무의미한 검증의 코드입니다. 절대 실패하지 않습니다.

// * WillRepeatedly 가장 마지막에 한번만 사용이 가능합니다.

using testing::Return;

int Add(int a, int b) { return a + b; }
struct Adder {
    int operator()(int a, int b) const { return a + b; }
};

TEST(CalcTest, Sample3)
{
    MockCalc mock;

    EXPECT_CALL(mock, Add(10, 20))
        .WillOnce(Return(100))
        .WillRepeatedly(Return(42));

    std::cout << mock.Add(10, 20) << std::endl;
    // std::cout << mock.Add(10, 20) << std::endl;
    // std::cout << mock.Add(10, 20) << std::endl;
    // std::cout << mock.Add(10, 20) << std::endl;
}

/*
TEST(CalcTest, Sample2)
{
    MockCalc mock;

    EXPECT_CALL(mock, Add(10, 20))
        .WillOnce(Return(30))
        .WillOnce(Return(100))
        .WillRepeatedly(Return(42));

    std::cout << mock.Add(10, 20) << std::endl;
    std::cout << mock.Add(10, 20) << std::endl;
    std::cout << mock.Add(10, 20) << std::endl;
    std::cout << mock.Add(10, 20) << std::endl;
    std::cout << mock.Add(10, 20) << std::endl;
    std::cout << mock.Add(10, 20) << std::endl;
    std::cout << mock.Add(10, 20) << std::endl;
    std::cout << mock.Add(10, 20) << std::endl;
}
*/

TEST(CalcTest, Sample)
{
    MockCalc mock;

    EXPECT_CALL(mock, Add(10, 20))
        .WillOnce(Return(30)); // !!!

    EXPECT_CALL(mock, Sub(100, 50));

    Process(&mock);
}
