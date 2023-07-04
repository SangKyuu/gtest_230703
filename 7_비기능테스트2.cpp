// 7_비기능테스트2.cpp
#include <iostream>
#include <string>

class Image {
    std::string url;

public:
    Image(const std::string& s)
        : url(s)
    {
    }

    void Draw() const
    {
        std::cout << "Draw Image " << url << std::endl;
    }

    //-----
    static int allocCount;
    void* operator new(size_t size)
    {
        ++allocCount;
        return malloc(size);
    }

    void operator delete(void* p, size_t)
    {
        --allocCount;
        free(p);
    }
    //-----
};

int Image::allocCount = 0;

bool DrawImage(const std::string& url)
{
    Image* image = new Image(url);
    image->Draw();

    // delete image;

    return true;
}

#include <gtest/gtest.h>

// SUT에 대해서, 메모리 누수가 발생하는지 여부도 검증하고 싶습니다.
// > SUT에 메모리 누수를 검증하기 위한 코드가 포함되어야 합니다.
//  new
// 1) 메모리 할당 => operator new
// 2) 생성자 호출

//  delete
// 1) 소멸자 호출
// 2) 메모리 해지 => operator delete

TEST(ImageTest, DrawImage)
{
    int alloc = Image::allocCount;

    EXPECT_TRUE(DrawImage("https://a.com/a.jpg"));

    int diff = Image::allocCount - alloc;
    EXPECT_EQ(diff, 0) << diff << " object(s) leaked";
}
