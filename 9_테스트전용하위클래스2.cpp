// 9_테스트전용하위클래스2.cpp
#include <iostream>

class Engine {
public:
    virtual ~Engine() { }

    // 부모가 제공하는 함수가 가상함수입니다.
    virtual void Start()
    {
        // ...
        std::cout << "Engine Start" << std::endl;
        // ...
    }
};

class Car {
    Engine* engine;

public:
    Car(Engine* p)
        : engine(p)
    {
    }

    void Go() const
    {
        // ...
        engine->Start();
        // ...
    }
};

#include <gtest/gtest.h>

// 전제
// => 부모가 제공하는 함수가 반드시 가상함수이어야 합니다.

// Car의 Go가 호출되었을 때, Engine의 Start가 제대로 호출되었는지 여부를
// 검증하고 싶습니다.
class TestEngine : public Engine {
    bool isStart = false;

public:
    void Start() override
    {
        // 부모의 기능을 호출합니다.
        Engine::Start();
        isStart = true;
    }

    // 테스트에서 확인할 수 있는 기능을 제공합니다.
    bool IsStart() const { return isStart; }
};

TEST(CarTest, Go)
{
    TestEngine engine;
    Car car(&engine);

    car.Go();

    EXPECT_TRUE(engine.IsStart());
}

#if 0
TEST(CarTest, Go)
{
    Engine engine;
    Car car(&engine);

    car.Go();

    // 문제점
    // => Engine에서 확인할 수 있는 기능을 제공하고 있지 않습니다.
}
#endif
