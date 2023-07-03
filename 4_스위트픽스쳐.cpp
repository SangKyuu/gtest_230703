// 4_스위트픽스쳐.cpp
#include <unistd.h>
#include <string>

class Terminal {
public:
    void Connect() { }
    void Disconnect() { }

    void Login(const std::string& id, const std::string& password) { }
    void Logout() { }

    bool IsLogin() { return false; }
};

//---------------
#include <gtest/gtest.h>

class TerminalTest : public testing::Test {
protected:
    Terminal* ts = nullptr;

    void SetUp() override
    {
        ts = new Terminal;
        ts->Connect();
    }

    void TearDown() override
    {
        ts->Disconnect();
        delete ts;
    }
};

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
