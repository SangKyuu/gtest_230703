// 2_3A.cpp
// SUT(System Under Test, 테스트 대상 시스템)
// - CUT(Class Under Test / Code Under Test)
class Calc {
public:
    double Display() { return 0.0; }

    void Enter(double n) { }
    void PressPlus() { }
    void PressMinus() { }
    void PressEquals() { }
};

#include <gtest/gtest.h>

// 1. TestCase 구성 하는 방법
//  => Test Suite 이름
//   : 테스트 대상 클래스(모듈)의 이름의 마지막에
//     Test, Spec 접미를 붙이는 형태로 많이 사용합니다.

// 2. Google Test에서 테스트케이스를 만드는 방법
//  => TEST(TestSuite 이름, TestCase 이름)
TEST(CalcTest, PressPlus)
{
    // 작성 중인 테스트는 명시적으로 테스트가 실패해야 합니다.
    //  > 실패의 원인을 작성해주어야 합니다.
    FAIL() << "작성 중입니다.";
}

TEST(CalcTest, PressMinus)
{
}
