// 5_전역픽스쳐.cpp
// => Test Fixture / Test Suite Fixture
//    xUnit Test Framework이 공통적으로 제공하는 기능입니다.
// => Google Test가 제공하는 기능입니다.
// => 프로그램의 시작/끝에 픽스쳐를 설치하거나 해체할 수 있는 기능을 제공합니다.

#include <gtest/gtest.h>

TEST(SampleTest, foo) { }
TEST(SampleTest, goo) { }

TEST(ImageTest, foo) { }
TEST(ImageTest, goo) { }

// 전역 픽스쳐를 사용하는 방법
// 1) testing::Enviroment의 자식 클래스를 정의합니다.
class MyEnvironment : public testing::Environment {
public:
    void SetUp() override
    {
        std::cout << "MyEnvironment.SetUp()" << std::endl;
    }

    void TearDown() override
    {
        std::cout << "MyEnvironment.TearDown()" << std::endl;
    }
};

// 2) 등록하는 방법
//   - 전역 변수
testing::Environment* myEnv1 = testing::AddGlobalTestEnvironment(
    new MyEnvironment);

//   - main 함수
