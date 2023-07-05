// 17_Mocking2.cpp
#include <gmock/gmock.h>

struct Element { }; // Dummy

class Calc {
public:
    virtual ~Calc() { }

    virtual int Add(Element x) { return 0; } // 행위 기반 검증 대상 X
    virtual int Add(int times, Element x) { return 0; } // 행위 기반 검증 대상 O
};

//----------
// => 상속을 위한 클래스도 Mocking을 통해 행위 기반 검증을 수행할 수 있습니다.
class MockCalc : public Calc {
public:
    // 행위 기반 검증의 대상 메소드만 Mocking 하면 됩니다.
    // int Add(int times, Element x) override
    MOCK_METHOD(int, Add, (int times, Element x), (override));

    // * 주의사항
    // : 행위 기반 검증을 위해 MOCK_METHOD한 함수와 동일한 이름의 오버로딩 함수가
    // 존재한다면, MOCK_METHOD에 의해서 이름이 가려집니다.
    // * 해결 방법
    //  > 명시적으로 동일한 이름의 함수의 선언이 필요합니다.
    using Calc::Add;
};

TEST(CalcTest, Add)
{
    MockCalc mock;

    mock.Add(Element());
    mock.Add(10, Element());
}
