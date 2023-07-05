// 19_Delegating.cpp
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
};

// Google Mock은 MOCK_METHOD한 메소드의 행위 기반 검증 뿐 아니라,
// 결과를 제어하는 기능을 제공하고 있습니다.
// => Delegating
//  : ON_CALL

using testing::Return;

int Add(int a, int b) { return a + b; }
struct Adder {
    int operator()(int a, int b) const { return a + b; }
};

TEST(CalcTest, Sample)
{
    MockCalc mock;
    // ON_CALL(mock, Add(10, 20)).WillByDefault(Return(30));
    // ON_CALL(mock, Add).WillByDefault(Return(30));

    // ON_CALL(mock, Add).WillByDefault(&Add); // 함수
    // ON_CALL(mock, Add).WillByDefault(Adder()); // 함수 객체
    ON_CALL(mock, Add).WillByDefault([](int a, int b) { return a + b; }); // 람다 표현식

    // EXPECT_CALL(mock, Add(10, 20));
    // EXPECT_CALL(mock, Sub(100, 50));

    // Process(&mock);

    std::cout
        << mock.Add(100, 200) << std::endl;
}
