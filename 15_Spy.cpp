// 15_Spy.cpp
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

// Test Spy Pattern
//  의도: SUT의 함수를 호출하였을 때, 발생하는 부수효과를 관찰할 수 없어서
//       테스트되지 않은 요구사항이 존재합니다.
//  방법: 목격한 일을 기록해두었다가 나중에 테스트에서 확인할 수 있도록 만들어진 테스트 대역
//    "다른 컴포넌트로부터의 간접 출력"을 저장해두었다가, 검증에 이용합니다.
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
