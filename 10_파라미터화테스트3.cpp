// 10_파라미터화테스트4.cpp
#include <gtest/gtest.h>

enum Color {
    RED,
    WHITE,
    BLACK
};

std::vector<std::string> cars = {
    "Sonata",
    "Avante",
    "Genesis",
};

// tuple을 이용해야 합니다.
using CarType = std::tuple<std::string, Color>;

class CarTest : public testing::TestWithParam<CarType> { };

// 2개 이상의 데이터를 조합할 때는 testing::Combine 함수를 사용해야 합니다.
INSTANTIATE_TEST_SUITE_P(CarValues, CarTest,
    testing::Combine(
        testing::ValuesIn(cars),
        testing::Values(RED, WHITE, BLACK)));

TEST_P(CarTest, Sample)
{
    const CarType& data = GetParam();

    std::string car = std::get<0>(data);
    Color color = std::get<1>(data);

    std::cout << car << ", " << color << std::endl;
}
