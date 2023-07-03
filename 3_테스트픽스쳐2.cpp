//  3_테스트픽스쳐2.cpp
class Calc {
public:
    //---- 요구사항의 변경
    // Calc(int n) { }
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
//  > 픽스쳐 설치에 관한 코드를 별도의 "테스트 유틸리티 함수"를 통해 캡슐화합니다.
//  * 테스트 스위트 안에서만 사용할 수 있는 테스트 유틸리티 함수를 제공해 주어야 합니다.

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
