// 13_Stub.cpp
#include <iostream>
#include <string>

class Time {
public:
    virtual ~Time() { }

    virtual std::string GetCurrentTime() const = 0;
};

class Clock : public Time {
public:
    std::string GetCurrentTime() const override
    {
        time_t rawTime;
        tm* timeInfo;
        char buffer[80];

        time(&rawTime);
        timeInfo = localtime(&rawTime);

        strftime(buffer, sizeof(buffer), "%H:%M", timeInfo);

        return std::string(buffer);
    }
};

class User {
    Time* time;

public:
    User(Time* p)
        : time(p)
    {
    }

    int Alarm()
    {
        std::string current = time->GetCurrentTime();
        if (current == "00:00") {
            // ...
            return 42;
        }

        if (current == "10:00") {
            // ...
            return 100;
        }

        return 0;
    }
};

#include <gtest/gtest.h>

// Test Stub Pattern
//  의도: 다른 컴포넌트로부터의 간접 입력에 의존하는 로직을 독립적으로 검증하고 싶다.
//  방법: 실제 의존하는 객체를 테스트 대역으로 교체해서,
//       SUT가 테스트하는데 필요한 결과를 보내도록 제어합니다.

class StubTime : public Time {
    std::string result;

public:
    StubTime(const std::string& time)
        : result(time)
    {
    }

    std::string GetCurrentTime() const override
    {
        return result;
    }
};

TEST(UserTest, Alarm_10)
{
    // Clock clock;
    StubTime clock("10:00");
    User user(&clock);

    EXPECT_EQ(user.Alarm(), 100);
}

TEST(UserTest, Alarm_00)
{
    // Clock clock;
    StubTime clock("00:00");
    User user(&clock);

    EXPECT_EQ(user.Alarm(), 42);
}

#if 0
int main()
{
    Clock c;
    std::cout << c.GetCurrentTime() << std::endl;
}
#endif
