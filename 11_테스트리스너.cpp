// 11_테스트리스너.cpp
// => Google Test의 기능입니다.
//  : 모든 테스트의 과정에 수행하는 작업을 정의할 수 있습니다.

#include <gtest/gtest.h>

TEST(SampleTest, foo) { }
TEST(SampleTest, goo) { }

// 테스트 리스너를 정의하는 방법
// class MyTestListener : public testing::TestEventListener {

using testing::TestSuite;

class MyTestListener : public testing::EmptyTestEventListener {
public:
    void OnTestSuiteStart(const TestSuite& test_suite) override
    {
        std::cout << test_suite.name() << std::endl;
    }

    void OnTestSuiteEnd(const TestSuite& test_suite) override
    {
        std::cout << test_suite.name() << std::endl;
    }
};

// 이벤트 리스너를 등록하는 방법
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    testing::TestEventListeners& listeners = testing::UnitTest::GetInstance()->listeners();
    listeners.Append(new MyTestListener);

    delete listeners.Release(listeners.default_result_printer());

    return RUN_ALL_TESTS();
}
