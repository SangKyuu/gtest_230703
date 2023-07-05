// 17_Mocking6.cpp
enum Level {
    INFO,
};

class Logger {
public:
    virtual ~Logger() { }

    virtual void Send(Level level,
        const char* dir,
        const char* file,
        const char* message)
        = 0;
};

class Car {
public:
    void Start(Logger* logger)
    {
        // ...
        logger->Send(INFO, "/tmp22", "car.log", "car start...");
        // ...
    }
};

// 테스트를 수행하면서, 관심 없는 인자에 대한 검증을 수행할 때
// => Car의 Start에서 Logger를 이용해서 INFO, "/tmp" 두가지 정보에 대해서만
//    검증을 수행하고 싶습니다.
#include <gmock/gmock.h>

class MockLogger : public Logger {
public:
#if 0
    void Send(Level level,
        const char* dir,
        const char* file,
        const char* message) override
#endif

    // 관심 있는 인자를 가지는 형태로 MOCK_METHOD를 작성합니다.
    // => Mocking 간략화
    MOCK_METHOD(void, Send, (Level level, const char* dir));

    void Send(Level level,
        const char* dir,
        const char* file,
        const char* message) override
    {
        // MOCK_METHOD한 메소드를 호출합니다.
        Send(level, dir);
    }
};

TEST(CarTest, Sample)
{
    MockLogger mock;
    Car car;

    EXPECT_CALL(mock, Send(INFO, "/tmp"));

    car.Start(&mock);
}
