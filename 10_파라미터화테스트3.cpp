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

int years[] = { 2022, 2023, 2024 };

// tuple을 이용해야 합니다.
using CarType = std::tuple<std::string, Color, int>;

class CarTest : public testing::TestWithParam<CarType> { };

// 2개 이상의 데이터를 조합할 때는 testing::Combine 함수를 사용해야 합니다.
INSTANTIATE_TEST_SUITE_P(CarValues, CarTest,
    testing::Combine(
        testing::ValuesIn(cars),
        testing::Values(RED, WHITE, BLACK),
        testing::ValuesIn(years)));

TEST_P(CarTest, Sample)
{
    const CarType& data = GetParam();

    std::string car = std::get<0>(data);
    Color color = std::get<1>(data);
    int year = std::get<2>(data);

    std::cout << car << ", " << color << ", " << year << std::endl;
}
