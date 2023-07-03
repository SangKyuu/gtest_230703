// 4_스위트픽스쳐.cpp
#include <unistd.h>
#include <string>

class Terminal {
public:
    // 가정: Connect / Disconnect가 느립니다.
    void Connect() { sleep(2); }
    void Disconnect() { sleep(1); }

    void Login(const std::string& id, const std::string& password) { }
    void Logout() { }

    bool IsLogin() { return false; }
};

//---------------
// 문제점
// - SetUp / TearDown이 느려서(픽스쳐 설치와 해체가 느려서)
//   테스트케이스가 추가될 때마다 전체적인 테스트의 수행 시간이 늘어납니다.
//  "Slow Test 문제"
//   * 테스트가 너무 느려서, 테스트를 수행하는 개발자의 생산성을 떨어뜨립니다.
//   * 테스트가 너무 느려서, 코드 변경되어도 아무도 테스트를 수행하지 않습니다.

// 해결방법
// => xUnit Test Framework은 스위트 픽스쳐 설치/해체의 기능을 제공하고 있습니다.
//   : 객체를 생성하기 전에 호출되고, 객체를 파괴한 후 호출될 수 있습니다.
//     "정적 메소드"
// => 이제는 더 이상 "신선한 픽스쳐" 전략이 아닌 "공유 픽스쳐" 전략입니다.
//    이전의 테스트 케이스로 인해서 픽스쳐의 상태가 망가지면, 이후의 테스트가
//    성공해야 하는 테스트임에도 실패하거나, 실패해야 하는 테스트임에도 성공하는
//    "변덕스러운 테스트" 문제가 발생할 수 있습니다.

// ------ Suite Fixture SetUp -----
// TerminalTest* ts = new TerminalTest;
// ts->SetUp();
// ts->TestCase();
// ts->TearDown();
// delete ts;

// TerminalTest* ts = new TerminalTest;
// ts->SetUp();
// ts->TestCase();
// ts->TearDown();
// delete ts;
// ...
// ------ Suite Fixture TearDown -----

#include <gtest/gtest.h>

class TerminalTest : public testing::Test {
protected:
    // Terminal* ts = nullptr;
    static Terminal* ts;

    static void SetUpTestSuite()
    {
        std::cout << "SetUpTestSuite" << std::endl;
        ts = new Terminal;
        ts->Connect();
    }

    static void TearDownTestSuite()
    {
        std::cout << "TearDownTestSuite" << std::endl;
        ts->Disconnect();
        delete ts;
    }

    void SetUp() override
    {
        // ts = new Terminal;
        // ts->Connect();
    }

    void TearDown() override
    {
        // ts->Disconnect();
        // delete ts;
    }
};

// 정적 멤버 데이터는 외부에 정의가 필요합니다.
Terminal* TerminalTest::ts = nullptr;

TEST_F(TerminalTest, Login)
{
    ts->Login("test_id", "test_password");

    ASSERT_TRUE(ts->IsLogin()) << "로그인 하였을 때";
}

TEST_F(TerminalTest, Logout)
{
    ts->Login("test_id", "test_password");
    ts->Logout();

    ASSERT_FALSE(ts->IsLogin()) << "로그아웃 하였을 때";
}

TEST_F(TerminalTest, Sample1) { }
TEST_F(TerminalTest, Sample2) { }

#if 0
// 아래의 코드를 암묵적 설치 / 해체를 이용해서 작성해보세요.
TEST(TerminalTest, Login)
{
    Terminal* ts = new Terminal;
    ts->Connect();

    ts->Login("test_id", "test_password");

    ASSERT_TRUE(ts->IsLogin()) << "로그인 하였을 때";

    ts->Disconnect();
    delete ts;
}

TEST(TerminalTest, Logout)
{
    Terminal* ts = new Terminal;
    ts->Connect();

    ts->Login("test_id", "test_password");
    ts->Logout();

    ASSERT_FALSE(ts->IsLogin()) << "로그아웃 하였을 때";

    ts->Disconnect();
    delete ts;
}
#endif
