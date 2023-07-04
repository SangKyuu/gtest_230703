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

#include <gtest/gtest.h>
#include <algorithm>

class SpyTarget : public DLoggerTarget {
    std::vector<std::string> history;

    std::string concat(Level level, const std::string& message)
    {
        return message + std::to_string(level);
    }

public:
    void Write(Level level, const std::string& message) override
    {
        // 목격한 일을 기록합니다.
        history.push_back(concat(level, message));
    }

    // 테스트를 통해 결과를 확인할 수 있는 기능을 제공합니다.
    bool IsReceived(Level level, const std::string& message)
    {
        return std::find(
                   std::begin(history), std::end(history),
                   concat(level, message))
            != end(history);
    }
};

TEST(DLoggerTest, Write)
{
    DLogger logger;
    SpyTarget spy1, spy2;
    logger.AddTarget(&spy1);
    logger.AddTarget(&spy2);

    logger.Write(INFO, "test_message");

    EXPECT_TRUE(spy1.IsReceived(INFO, "test_message"));
    EXPECT_TRUE(spy2.IsReceived(INFO, "test_message"));
}
