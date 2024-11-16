#include <gtest/gtest.h>
#include "lab.h"

TEST(TrapeciaTest, CalculateArea) {
    // Arrange
    Trapecia<double> trapecia(5, 10, 4);

    // Act
    double area = static_cast<double>(trapecia);

    // Assert
    ASSERT_DOUBLE_EQ(area, 30.0);
}

TEST(TrapeciaTest, CheckCenter) {
    // Arrange
    Trapecia<double> trapecia(4, 6, 8);

    // Act
    std::unique_ptr<Point<double>> center = trapecia.center();

    // Assert
    ASSERT_DOUBLE_EQ(center->x, 5.0);
    ASSERT_DOUBLE_EQ(center->y, 4.0);
}

TEST(RombTest, CalculateArea) {
    // Arrange
    Romb<double> romb(6, 8);

    // Act
    double area = static_cast<double>(romb);

    // Assert
    ASSERT_DOUBLE_EQ(area, 24.0);
}

TEST(RombTest, CheckCenter) {
    // Arrange
    Romb<double> romb(6, 8);

    // Act
    std::unique_ptr<Point<double>> center = romb.center();

    // Assert
    ASSERT_DOUBLE_EQ(center->x, 3.0);
    ASSERT_DOUBLE_EQ(center->y, 4.0);
}

TEST(PentaTest, CalculateArea) {
    // Arrange
    Penta<double> penta(5);

    // Act
    double area = static_cast<double>(penta);

    // Assert
    ASSERT_NEAR(area, 43.0119, 1e-4);
}

TEST(PentaTest, CheckCenter) {
    // Arrange
    Penta<double> penta(5);

    // Act
    std::unique_ptr<Point<double>> center = penta.center();

    // Assert
    ASSERT_NEAR(center->x, 4.045, 1e-3);
    ASSERT_NEAR(center->y, 2.938, 1e-3);
}

TEST(ArrayTest, AddAndRemoveElements) {
    // Arrange
    Array<int> array;

    // Act
    array.add(1);
    array.add(2);
    array.add(3);
    array.remove(1);

    // Assert
    ASSERT_EQ(array.getSize(), 2);
    ASSERT_EQ(array[0], 1);
    ASSERT_EQ(array[1], 3);
}

TEST(ArrayTest, Resize) {
    // Arrange
    Array<int> array;

    // Act
    for (int i = 0; i < 100; ++i) {
        array.add(i);
    }

    // Assert
    ASSERT_EQ(array.getSize(), 100);
    ASSERT_EQ(array[99], 99);
}
