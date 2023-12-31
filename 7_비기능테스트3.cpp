// 7_비기능테스트2.cpp
#include <iostream>
#include <string>

#ifdef GTEST_LEAK_TEST
#define DECLARE_LEAK_TEST()               \
    static int allocCount;                \
    void* operator new(size_t size)       \
    {                                     \
        ++allocCount;                     \
        return malloc(size);              \
    }                                     \
    void operator delete(void* p, size_t) \
    {                                     \
        --allocCount;                     \
        free(p);                          \
    }

#define IMPLEMENTS_LEAK_TEST(classname) \
    int classname::allocCount = 0;
#else
#define DECLARE_LEAK_TEST()
#define IMPLEMENTS_LEAK_TEST(classname)
#endif

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

    DECLARE_LEAK_TEST()
};

IMPLEMENTS_LEAK_TEST(Image)

bool DrawImage(const std::string& url)
{
    Image* image = new Image(url);
    image->Draw();

    // delete image;

    return true;
}

#include <gtest/gtest.h>

// 명시적인 TestSuite 클래스를 통해서
// 누수의 검증을 수행합니다.
class ImageTest : public testing::Test {
    int alloc = 0;

public:
    void SetUp() override
    {
#ifdef GTEST_LEAK_TEST
        alloc = Image::allocCount;
#endif
    }

    void TearDown() override
    {
#ifdef GTEST_LEAK_TEST
        int diff = Image::allocCount - alloc;
        EXPECT_EQ(diff, 0) << diff << " object(s) leaked";
#endif
    }
};

TEST_F(ImageTest, DrawImage)
{
    EXPECT_TRUE(DrawImage("https://a.com/a.jpg"));
}

// g++ 7_비기능테스트3.cpp -I./googletest/googletest/include -L. -lgtest -pthread -DGTEST_LEAK_TEST
