// 18_Mock종류.cpp
#include <string>

class Car {
public:
    virtual ~Car() { }

    virtual void Go() { }
    virtual std::string GetName() const { return "Sonata"; }
};

void Process(Car* car)
{
    // ...
    car->Go();
    car->GetName();
    // ...
}

#include <gmock/gmock.h>

/*
GMOCK WARNING:
Uninteresting mock function call - returning default value.
    Function call: GetName()
          Returns: ""
이유: MOCK_METHOD한 메소드가 EXPECT_CALL을 하지 않았는데,
//   내부적으로 호출이 수행된 경우, 경고가 발생합니다.

// 1. Naggy Mock(기본)
// => 테스트의 결과는 성공이지만, 관심 없는 호출에 대한 경고가 발생합니다.

// 2. Nice Mock
// => 테스트의 결과도 성공이고, 경고도 발생하지 않습니다.

// 3. Strict Mock
// => 테스트가 실패합니다.
// => 테스트의 통과 기준이 높아질 수 있습니다.
//    "테스트를 작성하는 비용의 증가가 발생할 수 있습니다."
*/

class MockCar : public Car {
public:
    MOCK_METHOD(void, Go, (), (override));
    MOCK_METHOD(std::string, GetName, (), (const, override));
};

using testing::NiceMock;
using testing::StrictMock;

TEST(CarTest, Process)
{
    // MockCar mock;
    // NiceMock<MockCar> mock;
    StrictMock<MockCar> mock;

    EXPECT_CALL(mock, Go());

    Process(&mock);
}
