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
