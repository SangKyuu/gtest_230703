//  3_테스트픽스쳐2.cpp
class Calc {
public:
    //---- 요구사항의 변경
    Calc(int n) { }
    //----

    double Display() { return 0.0; }

    void Enter(double n) { }
    void PressPlus() { }
    void PressMinus() { }
    void PressEquals() { }
};

#include <gtest/gtest.h>

// 1. Test Fixture
// 정의: xUnit Test Frmework에서 SUT를 실행하기 위해 준비해야 하는 모든 것을
//      테스트 픽스쳐 라고 합니다.
//      테스트 픽스쳐를 구성하는 모든 코드의 로직 부분을 "픽스쳐 설치" 라고 합니다.

// 2. Test Fixture 설치하는 방법 3가지

// 2) Delegate Setup(위임 설치)

TEST(CalcTest, PressPlus)
{
    Calc* calc = new Calc;

    calc->Enter(10);
    calc->PressPlus();
    calc->Enter(10);
    calc->PressEquals();

    ASSERT_EQ(calc->Display(), 20) << "10 + 10 하였을 때";
}

TEST(CalcTest, PressMinus)
{
    Calc* calc = new Calc;

    calc->Enter(10);
    calc->PressMinus();
    calc->Enter(10);
    calc->PressEquals();

    ASSERT_EQ(calc->Display(), 0) << "10 - 10 하였을 때";
}
