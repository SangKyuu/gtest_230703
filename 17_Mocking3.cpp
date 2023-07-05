// 17_Mocking3.cpp
#include <gmock/gmock.h>

// 템플릿으로 구현된 인터페이스
template <typename T>
class StackInterface {
public:
    virtual ~StackInterface() { }

    virtual int GetSize() const = 0;
    virtual void Push(const T& data) = 0;
};

// 템플릿으로 구현된 인터페이스/추상 클래스도 Mocking이 가능합니다.
template <typename T>
class MockStackInterface : public StackInterface<T> {
public:
    MOCK_METHOD(int, GetSize, (), (const, override));
    MOCK_METHOD(void, Push, (const T& data), (override));
};

TEST(StackInterfaceTest, Sample)
{
    MockStackInterface<int> mock;

    EXPECT_CALL(mock, GetSize());
    EXPECT_CALL(mock, Push(10));
}
