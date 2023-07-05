// 17_Mocking.cpp
#include <string>
#include <map>
#include <utility>

// 협력 객체의 인터페이스
class MP3 {
public:
    virtual ~MP3() { }

    virtual void Play() = 0;
    virtual void Stop(int n) = 0;

    virtual std::string GetTitle() const = 0;
    virtual void Go() const noexcept = 0;

    virtual std::pair<bool, int> GetPair() const = 0;
    virtual bool CheckMap(std::map<int, double> a, bool b) const = 0;
};

#include <gmock/gmock.h>

// 협력 객체의 인터페이스를 Mocking 합니다.
class MockMP3 : public MP3 {
public:
    // MOCK_METHOD(반환 타입, 함수 이름, (인자 정보), (한정자 정보));

    // void Play() override {}
    MOCK_METHOD(void, Play, (), (override));
    MOCK_METHOD(void, Stop, (int n), (override));

    // std::string GetTitle() const override {}
    MOCK_METHOD(std::string, GetTitle, (), (const, override));
    MOCK_METHOD(void, Go, (), (const, noexcept, override));

    // 주의사항: 템플릿의 타입 인자가 2개 이상인 경우
    //         괄호로 묶어주어야 합니다.

    // std::pair<bool, int> GetPair() const override
    MOCK_METHOD((std::pair<bool, int>), GetPair, (), (const, override));

    // bool CheckMap(std::map<int, double> a, bool b) const override
    MOCK_METHOD(bool, CheckMap, ((std::map<int, double> a), bool b), (const, override));
};

TEST(MP3Test, Sample)
{
    MockMP3 mock; // !!!
}
