// 3_테스트픽스쳐4.cpp
#include <gtest/gtest.h>

class ImageProcessorTest : public testing::Test {
protected:
    ImageProcessorTest() { std::cout << "ImageProcessorTest()" << std::endl; }
    ~ImageProcessorTest() { std::cout << "~ImageProcessorTest()" << std::endl; }

    void SetUp() override { std::cout << "SetUp()" << std::endl; }
    void TearDown() override { std::cout << "TearDown()" << std::endl; }
};

TEST_F(ImageProcessorTest, ResizeImage) { std::cout << "ResizeImage" << std::endl; }
TEST_F(ImageProcessorTest, BlurImage) { std::cout << "BlurImage" << std::endl; }

// xUnit Test Framework이 테스트케이스를 수행하는 흐름
// => 각 테스트 케이스마다 새로운 테스트 스위트 클래스를 생성하고 파괴하는 정책을 사용하고 있습니다.
//  "신선한 픽스쳐 전략"

/*
ImageProcessorTest* ts = new ImageProcessorTest();
ts->SetUp();
ts->ResizeImage();
ts->TearDown();
delete ts;

ImageProcessorTest* ts = new ImageProcessorTest();
ts->SetUp();
ts->BlurImage();
ts->TearDown();
delete ts;
*/
