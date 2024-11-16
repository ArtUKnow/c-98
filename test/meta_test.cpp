#include "../include/figures.h"
#include <gtest/gtest.h>

// Тесты для шаблонного класса Point
TEST(PointTest, DefaultConstructor) {
    Point<int> p;
    EXPECT_EQ(p.getX(), 0);
    EXPECT_EQ(p.getY(), 0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point<double> p(3.5, -2.7);
    EXPECT_DOUBLE_EQ(p.getX(), 3.5);
    EXPECT_DOUBLE_EQ(p.getY(), -2.7);
}

TEST(PointTest, Setters) {
    Point<int> p;
    p.setX(10);
    p.setY(20);
    EXPECT_EQ(p.getX(), 10);
    EXPECT_EQ(p.getY(), 20);
}

// Тесты для класса Trapecia
TEST(TrapeciaTest, DefaultConstructor) {
    Trapecia<int> t;
    EXPECT_EQ(static_cast<double>(t), 1.0); // Площадь по умолчанию (1+1)*1/2
}

TEST(TrapeciaTest, ParameterizedConstructor) {
    Trapecia<double> t(3.0, 5.0, 2.0);
    EXPECT_DOUBLE_EQ(static_cast<double>(t), 8.0); // Площадь (3+5)*2/2
}

TEST(TrapeciaTest, CenterCalculation) {
    Trapecia<double> t(3.0, 5.0, 2.0);
    auto center = t.center();
    EXPECT_DOUBLE_EQ(center.first, 2.5);
    EXPECT_DOUBLE_EQ(center.second, 0.6666666667);
}

TEST(TrapeciaTest, ComparisonOperator) {
    Trapecia<int> t1(3, 5, 4);
    Trapecia<int> t2(3, 5, 4);
    Trapecia<int> t3(4, 5, 3);
    EXPECT_TRUE(t1 == t2);
    EXPECT_FALSE(t1 == t3);
}

// Тесты для класса Romb
TEST(RombTest, DefaultConstructor) {
    Romb<int> r;
    EXPECT_EQ(static_cast<double>(r), 0.5); // Площадь по умолчанию 1*1/2
}

TEST(RombTest, ParameterizedConstructor) {
    Romb<double> r(3.0, 4.0);
    EXPECT_DOUBLE_EQ(static_cast<double>(r), 6.0); // Площадь 3*4/2
}

TEST(RombTest, CenterCalculation) {
    Romb<double> r(6.0, 8.0);
    auto center = r.center();
    EXPECT_DOUBLE_EQ(center.first, 3.0);
    EXPECT_DOUBLE_EQ(center.second, 4.0);
}

TEST(RombTest, ComparisonOperator) {
    Romb<int> r1(4, 6);
    Romb<int> r2(4, 6);
    Romb<int> r3(5, 6);
    EXPECT_TRUE(r1 == r2);
    EXPECT_FALSE(r1 == r3);
}

// Тесты для класса Penta
TEST(PentaTest, DefaultConstructor) {
    Penta<int> p;
    EXPECT_NEAR(static_cast<double>(p), 1.72048, 0.0001); // Площадь по умолчанию
}

TEST(PentaTest, ParameterizedConstructor) {
    Penta<double> p(4.0);
    EXPECT_NEAR(static_cast<double>(p), 27.5276, 0.0001); // Площадь пятиугольника с стороной 4
}

TEST(PentaTest, CenterCalculation) {
    Penta<double> p(4.0);
    auto center = p.center();
    EXPECT_NEAR(center.first, 7.63932, 0.0001);
    EXPECT_NEAR(center.second, 2.93893, 0.0001);
}

TEST(PentaTest, ComparisonOperator) {
    Penta<int> p1(4);
    Penta<int> p2(4);
    Penta<int> p3(5);
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

// Тесты для динамического массива фигур
TEST(DynamicArrayTest, AddAndRetrieveFigures) {
    Array<std::shared_ptr<Figure<int>>> arr;
    arr.add(std::make_shared<Trapecia<int>>(3, 4, 5));
    arr.add(std::make_shared<Romb<int>>(6, 8));

    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(static_cast<double>(*arr[0]), 17.5); // Площадь Trapecia
    EXPECT_EQ(static_cast<double>(*arr[1]), 24.0); // Площадь Romb
}

TEST(DynamicArrayTest, TotalAreaCalculation) {
    Array<std::shared_ptr<Figure<int>>> arr;
    arr.add(std::make_shared<Trapecia<int>>(3, 4, 5));
    arr.add(std::make_shared<Romb<int>>(6, 8));
    arr.add(std::make_shared<Penta<int>>(4));

    double totalArea = 0;
    for (int i = 0; i < arr.size(); ++i) {
        totalArea += static_cast<double>(*arr[i]);
    }

    EXPECT_NEAR(totalArea, 17.5 + 24.0 + 27.5276, 0.0001);
}

TEST(DynamicArrayTest, DeleteFigureByIndex) {
    Array<std::shared_ptr<Figure<int>>> arr;
    arr.add(std::make_shared<Trapecia<int>>(3, 4, 5));
    arr.add(std::make_shared<Romb<int>>(6, 8));

    arr.remove(0); // Удаляем первую фигуру (Trapecia)
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(static_cast<double>(*arr[0]), 24.0); // Оставшаяся фигура - Romb
}
