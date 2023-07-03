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
//  > 픽스쳐 설치에 관한 코드를 별도의 "테스트 유틸리티 함수"를 통해 캡슐화합니다.
//  * 테스트 스위트 안에서만 사용할 수 있는 테스트 유틸리티 함수를 제공해 주어야 합니다.
//  => 명시적인 테스트 스위트 클래스가 필요합니다.

//          testing::Test / Test Case
//                 |
//      --------------------------------
//      |                              |
// CalcTest_PressPlus_Test    CalcTest_PressMinus_Test

#if 0
// class CalcTest_PressPlus_Test : public ::testing::Test
TEST(CalcTest, PressPlus)
{
    Calc* calc = new Calc;

    calc->Enter(10);
    calc->PressPlus();
    calc->Enter(10);
    calc->PressEquals();

    ASSERT_EQ(calc->Display(), 20) << "10 + 10 하였을 때";
}

// class CalcTest_PressMinus_Test : public ::testing::Test
TEST(CalcTest, PressMinus)
{
    Calc* calc = new Calc;

    calc->Enter(10);
    calc->PressMinus();
    calc->Enter(10);
    calc->PressEquals();

    ASSERT_EQ(calc->Display(), 0) << "10 - 10 하였을 때";
}
#endif

// 명시적인 테스트 스위트 클래스
//          testing::Test
//                 |
//             CalcTest => 테스트 스위트 클래스(테스트 유틸리티 메소드)
//                 |
//      --------------------------------
//      |                              |
// CalcTest_PressPlus_Test    CalcTest_PressMinus_Test

// 1) testing::Test 자식 클래스를 정의합니다.
class CalcTest : public testing::Test {
protected:
    Calc* CreateCalc() { return new Calc(0); }
};

// 2) TEST_F를 통해 테스트 케이스를 만들어야 합니다.
// class CalcTest_PressPlus_Test : public CalcTest
TEST_F(CalcTest, PressPlus)
{
    Calc* calc = CreateCalc();

    calc->Enter(10);
    calc->PressPlus();
    calc->Enter(10);
    calc->PressEquals();

    ASSERT_EQ(calc->Display(), 20) << "10 + 10 하였을 때";
}

// class CalcTest_PressMinus_Test : public CalcTest
TEST_F(CalcTest, PressMinus)
{
    Calc* calc = CreateCalc();

    calc->Enter(10);
    calc->PressMinus();
    calc->Enter(10);
    calc->PressEquals();

    ASSERT_EQ(calc->Display(), 0) << "10 - 10 하였을 때";
}
