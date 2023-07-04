// 12_테스트대역2.cpp
#include <string>

// Test Double(테스트 대역)
//  목적: 테스트 환경을 통제하기 위해 사용합니다.
//  적용: 테스트 대역을 적용하기 위해서는, 제품 코드가 테스트 대역을
//       적용할 수 있는 설계가 적용되어 있어야 합니다.
//   => 약한 결합: 협력 객체를 이용할 때, 추상 타입(추상 클래스, 인터페이스)에 의존하는 것
//      강한 결합: 협력 객체를 이용할 때, 구체적인 타입에 의존하는 것

// * 인터페이스를 도입
class IFileSystem {
public:
    virtual ~IFileSystem() { }

    virtual bool IsValidFilename(const std::string& name) = 0;
};

class FileSystem : public IFileSystem {
public:
    bool IsValidFilename(const std::string& name) override
    {
        // ...
        // return true;
        return false;
    }
};

// Logger
//   IsValidLogFilename
//         ------------------> FileSystem
//                                  IsValidFilename

//                      <<interface>>
// Logger ----------->   IFileSystem
//                            |
//                        ----------
//                        |        |
//                   FileSystem   TestDouble

// * 약한 결합 핵심
//  => 협력 객체를 직접 생성하는 것이 아니라,
//     외부에서 생성해서 전달 받아야 합니다.
//     "의존성 주입(Dependency Injection)"
//     1) 생성자 주입
//      - 협력 객체가 필수적일 때
//     2) 메소드 주입
//      - 협력 객체가 필수적이지 않을 때

class Logger {
    IFileSystem* fs;

public:
    Logger(IFileSystem* p = nullptr)
        : fs(p)
    {
        // 기존의 제품 코드의 사용 방식을 그대로 이용할 수 있도록
        // 기본 협력 객체를 제공합니다.
        if (p == nullptr) {
            fs = new FileSystem;
        }
    }

    // 확장자를 제외한 파일명이 5글자 이상이어야 한다.
    // ex)
    //  file.log  ----> file (X)
    //  hello.log ----> hello (O)
    bool IsValidLogFilename(const std::string& filename)
    {
        //------ 테스트 대상 코드 -------
        size_t index = filename.find_last_of(".");
        std::string name = filename.substr(0, index);
        if (name.size() < 5) {
            return false;
        }
        //------ 테스트 대상 코드 -------

        return fs->IsValidFilename(filename);

        // FileSystem fs;
        // return fs.IsValidFilename(filename);
    }
};

//-----
#include <gtest/gtest.h>

// 테스트 대역은 협력 객체의 인터페이스를 기반으로 만듭니다.
class StubFileSystem : public IFileSystem {
public:
    bool IsValidFilename(const std::string& filename) override
    {
        return true;
    }
};

TEST(LoggerTest, IsValidLogFilename_NameLonggerThan5Chars_Returns_True)
{
    StubFileSystem stub;
    Logger logger(&stub);
    std::string validFilename = "valid.log";

    EXPECT_TRUE(logger.IsValidLogFilename(validFilename))
        << "확장자를 제외한 파일명이 다섯글자 이상일 때";
}

TEST(LoggerTest, IsValidLogFilename_NameShorterThan5Chars_Returns_False)
{
    StubFileSystem stub;
    Logger logger(&stub);
    std::string invalidFilename = "bad.log";

    EXPECT_FALSE(logger.IsValidLogFilename(invalidFilename))
        << "확장자를 제외한 파일명이 다섯글자 미만일 때";
}

// 테스트 대역은 용도와 목적에 따라 4가지가 있습니다.
// => xUnit Test Pattern
//    테스트 대역이라는 용어를 도입했습니다.

// 1) Test Stub
// 2) Fake Object
// 3) Test Spy
// 4) Mock Object
