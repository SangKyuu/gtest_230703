// 14_Fake.cpp
#include <string>

class User {
    std::string name;
    int age;

public:
    User(const std::string& s, int n)
        : name(s)
        , age(n)
    {
    }

    std::string GetName() const { return name; }
    int GetAge() const { return age; }
};

class IDatabase {
public:
    virtual ~IDatabase() { }

    virtual void SaveUser(const std::string& name, User* user) = 0;
    virtual User* LoadUser(const std::string& name) = 0;
};

class UserRepository {
    IDatabase* database;

public:
    UserRepository(IDatabase* p)
        : database(p)
    {
    }

    void Save(User* user)
    {
        database->SaveUser(user->GetName(), user);
    }

    User* Load(const std::string& name)
    {
        return database->LoadUser(name);
    }
};

#include <gmock/gmock.h>
#include <map>
bool operator==(const User& lhs, const User& rhs)
{
    return lhs.GetName() == rhs.GetName() && lhs.GetAge() == rhs.GetAge();
}

std::ostream& operator<<(std::ostream& os, const User& user)
{
    return os << "(" << user.GetName() << ", " << user.GetAge() << ")";
}

class FakeDatabase : public IDatabase {
    std::map<std::string, User*> data;

public:
    FakeDatabase()
    {
        ON_CALL(*this, SaveUser).WillByDefault([this](const std::string& name, User* user) {
            data[name] = user;
        });
        ON_CALL(*this, LoadUser).WillByDefault([this](const std::string& name) {
            return data[name];
        });
    }

    MOCK_METHOD(void, SaveUser, (const std::string& name, User* user), (override));
    MOCK_METHOD(User*, LoadUser, (const std::string& name), (override));
};

using testing::NiceMock;

TEST(UserRepositoryTest, Save)
{
    NiceMock<FakeDatabase> fake;
    UserRepository repo(&fake);
    std::string testName = "test_name";
    User expected(testName, 42);

    repo.Save(&expected);
    User* actual = repo.Load(testName);

    ASSERT_NE(actual, nullptr);
    EXPECT_EQ(*actual, expected);
}
