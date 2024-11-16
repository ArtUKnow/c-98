#include <gtest/gtest.h>
#include "../include/meta.h"

TEST(DynamicArrayTest, AddAndGetElement) {
    DynamicArray<std::shared_ptr<Figure<double>>> array;
    std::shared_ptr<Trapecia<double>> trap = std::make_shared<Trapecia<double>>(3, 4, 5);
    array.addFigure(trap);
    EXPECT_EQ(*array[0], *trap);
}

TEST(DynamicArrayTest, RemoveElement) {
    DynamicArray<std::shared_ptr<Figure<double>>> array;
    std::shared_ptr<Trapecia<double>> trap1 = std::make_shared<Trapecia<double>>(3, 4, 5);
    std::shared_ptr<Trapecia<double>> trap2 =std::make_shared<Trapecia<double>>(6, 7, 8);
    array.addFigure(trap1);
    array.addFigure(trap2);
    array.removeFigure(0);
    EXPECT_EQ(array.getSize(), 1);
    EXPECT_EQ(*array[0], *trap2);
}

TEST(DynamicArrayTest, CheckSizeAfterAddRemove) {
    DynamicArray<std::shared_ptr<Figure<double>>> array;
    std::shared_ptr<Trapecia<double>> trap1 = std::make_shared<Trapecia<double>>(3, 4, 5);
    std::shared_ptr<Trapecia<double>> trap2 = std::make_shared<Trapecia<double>>(6, 7, 8);
    array.addFigure(trap1);
    array.addFigure(trap2);
    EXPECT_EQ(array.getSize(), 2);
    array.removeFigure(0);
    EXPECT_EQ(array.getSize(), 1);
}

TEST(DynamicArrayTest, EmptyArray) {
    DynamicArray<std::shared_ptr<Figure<double>>> array;
    EXPECT_EQ(array.getSize(), 0);
    EXPECT_THROW(array[0], std::out_of_range);
}

TEST(DynamicArrayTest, TotalArea) {
    DynamicArray<std::shared_ptr<Figure<double>>> array;
    std::shared_ptr<Trapecia<double>> trap1 = std::make_shared<Trapecia<double>>(3, 4, 5);
    std::shared_ptr<Romb<double>> romb1= std::make_shared<Romb<double>>(6, 8);
    array.addFigure(trap1);
    array.addFigure(romb1);
    double totalArea = array.totalArea();
    EXPECT_EQ(totalArea, 17.5 + 24.0);
}

TEST(TrapeciaTest, AreaCalculation) {
    Trapecia<double> trap(3, 4, 5);
    double area = static_cast<double>(trap);
    EXPECT_DOUBLE_EQ(area, 17.5);
}

TEST(RombTest, AreaCalculation) {
    Romb<double> romb(6, 8);
    double area = static_cast<double>(romb);
    EXPECT_DOUBLE_EQ(area, 24.0);
}

TEST(RombTest, EqualityCheck) {
    Romb<double> romb1(6, 8);
    Romb<double> romb2(6, 8);
    Romb<double> romb3(5, 7);
    EXPECT_TRUE(romb1 == romb2);
    EXPECT_FALSE(romb1 == romb3);
}

TEST(RombTest, CenterCalculation) {
    Romb<double> romb(6, 8);
    std::unique_ptr<Point<double>> center = romb.center();
    EXPECT_DOUBLE_EQ(center->x, 0.0);
    EXPECT_DOUBLE_EQ(center->y, 0.0);
}

TEST(DynamicArrayTest, TotalAreaMultipleFigures) {
    DynamicArray<std::shared_ptr<Figure<double>>> array;
    std::shared_ptr<Trapecia<double>> trap1 = std::make_shared<Trapecia<double>>(3, 4, 5);
    std::shared_ptr<Romb<double>> romb1 = std::make_shared<Romb<double>>(6, 8);
    array.addFigure(trap1);
    array.addFigure(romb1);
    array.addFigure(penta1);
    double totalArea = array.totalArea();
    EXPECT_DOUBLE_EQ(totalArea, 41.5);
}
