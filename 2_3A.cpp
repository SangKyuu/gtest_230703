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

// 3. 테스트케이스를 작성하는 방법 - 3A
//   1) Arrange: 테스트 대상 코드를 초기화하고, 필요한 경우 설정하고 준비합니다.
//   2) Act: 테스트 대상 코드에 작용을 가합니다.
//   3) Assert: 기대하는 바를 단언합니다.

// 4. 테스트 코드의 품질
//   1) 가독성
//     - 테스트 코드의 구성
//     - 테스트 코드의 이름을 통해 테스트의 시나리오가 제대로 드러나는가?
//       테스트 코드의 실패 메세지를 통해 실패의 원인을 파악할 수 있는가?

//   2) 유지보수성
//     - 테스트 코드도 유지보수의 대상입니다.
//     - "유지보수의 비용이 최소화"되어야 합니다.
//     - 오류가 발생할 수 있는 가능성이 있는 코드는 단위 테스트에서
//       지양해야 합니다.
//       단위 테스트 케이스 안에서 제어 구문(조건문, 반복문, 예외 처리)의 발생을
//       최소화해야 합니다.

//   3) 신뢰성

#define SPEC printf

TEST(CalcTest, PressMinus)
{
    SPEC("10에서 5를 뺐을 때, 5가 나오지는 여부를 검증합니다.\n");

    // Arrange
    Calc* calc = new Calc;

    // Act
    calc->Enter(10);
    calc->PressMinus();
    calc->Enter(5);
    calc->PressEquals();

    // Assert
#if 0
    if (calc->Display() != 5) {
        FAIL() << "결과값이 5가 아닙니다.";
    } else {
        SUCCEED();
    }
#endif
    // xUnit Test Framework은 다양한 단언문을 제공하고 있습니다.
    // : ASSERT_EQ / NE / LT / LE / GT / GE ...
    ASSERT_EQ(calc->Display(), 5) << "10에서 5를 뺐을 때";
}
