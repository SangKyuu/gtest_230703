//  3_테스트픽스쳐.cpp
#include <iostream>
class Calc {
public:
    //---- 요구사항의 변경
    // Calc(int n) { }
    //----
    ~Calc() { std::cout << "~Calc()" << std::endl; }

    double Display() { return 0.0; }

    void Enter(double n) { }
    void PressPlus() { }
    void PressMinus() { }
    void PressEquals() { }
};

#include <gtest/gtest.h>

// 2. Test Fixture 설치하는 방법 3가지
// 3) Implicit Setup/Tear Down(암묵적 설치/해체)
// => xUnit Test Framework가 제공하는 기능입니다.
// 방법: 여러 테스트케이스에서 같은 테스트 픽스쳐 설치/해체의 코드를 암묵적으로 호출되는
//      함수를 통해서 처리합니다.
//      "명시적인 테스트 스위트 클래스를 제공해야 합니다."
// 장점: 테스트 코드 중복을 제거하고, 불필요한 준비 과정을 제거할 수 있다.
// 단점: 픽스쳐 설치 코드가 테스트 케이스 외부에 존재하기 때문에,
//      테스트케이스만으로 테스트 코드를 분석하기 어려울 수 있다.

class CalcTest : public testing::Test {
protected:
    Calc* calc = nullptr;

    void SetUp() override
    {
        std::cout << "CalcTest.SetUp()" << std::endl;
        calc = new Calc;
    }

    void TearDown() override
    {
        std::cout << "CalcTest.TearDown()" << std::endl;
        delete calc;
    }
};

TEST_F(CalcTest, PressPlus)
{
    calc->Enter(10);
    calc->PressPlus();
    calc->Enter(10);
    calc->PressEquals();

    ASSERT_EQ(calc->Display(), 20) << "10 + 10 하였을 때";
    // 단언문이 실패할 경우, 이후의 코드는 수행되지 않습니다.

    // delete calc;
}

TEST_F(CalcTest, PressMinus)
{
    calc->Enter(10);
    calc->PressMinus();
    calc->Enter(10);
    calc->PressEquals();

    ASSERT_EQ(calc->Display(), 0) << "10 - 10 하였을 때";

    // delete calc;
}
