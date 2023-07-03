//  3_테스트픽스쳐.cpp
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
// 1) Inline Fixture Setup
// : 모든 픽스쳐 설치를 테스트 케이스 안에서 수행합니다.
// 장점: 픽스쳐를 설치하는 과정과 검증의 로직이 하나의 테스트 케이스 함수안에서 드러나기 때문에
//      인과 관계를 분석하기 쉽다.
// 단점: 모든 테스트 코드 안에서 "테스트 코드 중복"이 발생합니다.

// 2) Delegate Setup(위임 설치)

// 3. 테스트 냄새
//  정의: 테스트 코드의 가독성 / 유지보수성 / 신뢰성을 떨어뜨리는 요솔

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
