// 16_Mock.cpp
#include <string>
#include <vector>

enum Level {
    INFO,
    WARN,
    ERROR
};

class DLoggerTarget {
public:
    virtual ~DLoggerTarget() { }

    virtual void Write(Level level, const std::string& message) = 0;
};

class FileTarget : public DLoggerTarget {
public:
    void Write(Level level, const std::string& message) override
    {
        // 로그를 파일에 기록합니다.
    }
};

class DLogger {
    std::vector<DLoggerTarget*> targets;

public:
    void AddTarget(DLoggerTarget* p) { targets.push_back(p); }

    void Write(Level level, const std::string& message)
    {
        for (auto e : targets) {
            e->Write(level, message);
        }
    }
};

// Mock Object Pattern
//  의도: SUT의 함수를 호출하였을 때, 발생하는 부수효과를 관찰할 수 없어서
//       테스트되지 않은 요구사항이 존재합니다.

//  방법: 행위 기반 검증을 수행합니다.
//       모의 객체(Mock Object) => 행위을 검증하기 위한 테스트 대역
//       "Mock Framework"을 이용합니다.
//     > Google Mock
//      원래는 별도의 프로젝트였지만, Google Test 프로젝트 흡수되었습니다.

//  상태 검증
// - 객체에 작용을 가한 후, 단언문을 통해 내부 상태값의 변화를 통해 검증을 수행합니다.
//  동작 검증
// - 객체에 작용을 가한 후, 내부적으로 발생하는 함수의 호출 여부, 호출 횟수, 호출 순서, 호출 인자
//   정보를 통해 정상 동작 여부를 검증합니다.

#include <gmock/gmock.h> // GoogleTest + GoogleMock

// Google Mock이 1.10 이후로 사용 방법이 변경되었습니다. => Mocking

// 모의 객체(테스트 대역)을 만들어야 합니다.
class MockDLoggerTarget : public DLoggerTarget {
public:
    // 행위 기반 검증을 수행하는 메소드에 대해서
    // 아래와 같이 작성을 해주어야 합니다.

    // 1.10 이전
    // : MOCK_METHOD{인자개수}(함수 이름, 함수 타입);
    // MOCK_METHOD2(Write, void(Level level, const std::string& message)); // Mocking

    // 1.10 이후
    // : MOCK_METHOD 하나의 매크로를 통해 변경되었습니다.
    // void Write(Level level, const std::string& message) override
    // => MOCK_METHOD(반환타입, 함수 이름, (인자 정보), (한정자 정보))
    MOCK_METHOD(void, Write, (Level level, const std::string& message), (override));
};

// 주의사항
// > Google Mock은 Act를 수행하기 전에 EXPECT_CALL을 먼저해야 합니다.
TEST(DLoggerTest, Write)
{
    // Arrange
    DLogger logger;
    MockDLoggerTarget mock1, mock2;
    logger.AddTarget(&mock1);
    logger.AddTarget(&mock2);

    // Assert
    // 행위 기반 검증을 수행할 수 있습니다.
    EXPECT_CALL(mock1, Write(INFO, "test_message"));
    EXPECT_CALL(mock2, Write(INFO, "test_message"));

    // Act
    logger.Write(INFO, "test_message");
}

// 테스트 대역(Test Double) => xUnit Test Pattern
// => Google Mock은 테스트 대역을 위한 프레임워크 입니다.

// 1) Test Stub
//  => SUT가 테스트하는데 필요한 결과를 테스트 대역을 통해 제어합니다.
//    "특수한 상황을 시뮬레이션 합니다."

// 2) Fake Object
// => 협력 객체가 준비되지 않았거나, 협력 객체가 사용하기 어렵거나, 협력 객체가 너무 느린 경우
//    같은 역활을 수행하는 가벼운 테스트 대역을 통해 SUT를 검증합니다.

// 3) Test Spy
// => 관찰할 수 있는 SUT의 부수효과가 존재하지 않는 경우,
//    협력 객체를 통해 목격한 일을 기록해두었다가, 테스트에서 확인합니다.

// 4) Mock Object
// => 관찰할 수 있는 SUT의 부수효과가 존재하지 않는 경우,
//    메소드의 호출 여부/순서/횟수/인자 등을 통해 검증합니다.
