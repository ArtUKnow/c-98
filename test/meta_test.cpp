#include <gtest/gtest.h>
#include "../include/meta.h"

TEST(DynamicArrayTest, AddRemoveFigures) {
    // Arrange
    DynamicArray<std::shared_ptr<Figure<double>>> array;

    auto trapezoid = std::make_shared<Trapecia<double>>(3, 4, 5);
    auto rhombus = std::make_shared<Romb<double>>(6, 8);

    // Act
    array.addFigure(trapezoid);
    array.addFigure(rhombus);

    // Assert
    ASSERT_EQ(array.getSize(), 2);
    EXPECT_DOUBLE_EQ(static_cast<double>(*array[0]), 17.5); // Площадь трапеции
    EXPECT_DOUBLE_EQ(static_cast<double>(*array[1]), 24.0); // Площадь ромба

    // Act
    array.removeFigure(0);

    // Assert
    ASSERT_EQ(array.getSize(), 1);
    EXPECT_DOUBLE_EQ(static_cast<double>(*array[0]), 24.0); // Оставшийся ромб
}

// Тест вычисления общей площади фигур
TEST(DynamicArrayTest, TotalArea) {
    // Arrange
    DynamicArray<std::shared_ptr<Figure<double>>> array;

    auto trapezoid = std::make_shared<Trapecia<double>>(3, 4, 5);
    auto rhombus = std::make_shared<Romb<double>>(6, 8);
    auto pentagon = std::make_shared<Penta<double>>(5);

    array.addFigure(trapezoid);
    array.addFigure(rhombus);
    array.addFigure(pentagon);

    // Act
    double totalArea = array.totalArea();

    // Assert
    EXPECT_DOUBLE_EQ(totalArea, 17.5 + 24.0 + 43.0119); // Сумма площадей всех фигур
}

// Тест Trapecia: центр фигуры
TEST(TrapeciaTest, CenterCalculation) {
    // Arrange
    Trapecia<double> trapezoid(3, 4, 5);

    // Act
    auto center = trapezoid.center();

    // Assert
    EXPECT_DOUBLE_EQ(center->x, 0.0);
    EXPECT_DOUBLE_EQ(center->y, 2.5); // Половина высоты
}

// Тест Romb: площадь и сравнение
TEST(RombTest, AreaAndEquality) {
    // Arrange
    Romb<double> romb1(6, 8);
    Romb<double> romb2(6, 8);
    Romb<double> romb3(5, 7);

    // Act
    double area1 = static_cast<double>(romb1);
    double area2 = static_cast<double>(romb2);

    // Assert
    EXPECT_DOUBLE_EQ(area1, 24.0);
    EXPECT_DOUBLE_EQ(area2, 24.0);
    EXPECT_TRUE(romb1 == romb2);
    EXPECT_FALSE(romb1 == romb3);
}

// Тест Penta: центр и площадь
TEST(PentaTest, CenterAndArea) {
    // Arrange
    Penta<double> pentagon(5);

    // Act
    auto center = pentagon.center();
    double area = static_cast<double>(pentagon);

    // Assert
    EXPECT_DOUBLE_EQ(center->x, 0.0);
    EXPECT_DOUBLE_EQ(center->y, 0.0);
    EXPECT_NEAR(area, 43.0119, 0.0001); // Округление из-за вычислений
}

// Тест DynamicArray: проверка ресайза
TEST(DynamicArrayTest, ResizeCapacity) {
    // Arrange
    DynamicArray<std::shared_ptr<Figure<double>>> array;

    // Act
    for (int i = 0; i < 15; ++i) {
        array.addFigure(std::make_shared<Trapecia<double>>(3, 4, 5));
    }

    // Assert
    EXPECT_EQ(array.getSize(), 15);
    EXPECT_GE(array.get_capacity(), 15); // Проверяем, что емкость увеличилась
}
