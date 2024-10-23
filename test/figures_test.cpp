#include "../include/figures.h"
#include <gtest/gtest.h>

TEST(FigureTest, TrapArea) {
    Trapecia trap(3.0, 5.0, 4.0);
    double area = static_cast<double>(trap);
    ASSERT_TRUE(area == 16.000);
}

TEST(FigureTest, TrapAreaZero) {
    Trapecia trap(0.0, 0.0, 0.0);
    double area = static_cast<double>(trap);
    ASSERT_TRUE(area == 0.0);
}

TEST(FigureTest, RombArea) {
    Romb romb(4.0, 5.0);
    double area = static_cast<double>(romb);
    ASSERT_TRUE(area == 10.000);
}

TEST(FigureTest, RombAreaZero) {
    Romb romb(0.0, 0.0);
    double area = static_cast<double>(romb);
    ASSERT_TRUE(area == 0.0);
}

TEST(FigureTest, PentaArea) {
    Penta penta(3.0);
    double area = static_cast<double>(penta);
    ASSERT_TRUE(area >= 15.483 && area <= 15.485);
}

TEST(FigureTest, PentaAreaZero) {
    Penta penta(0.0);
    double area = static_cast<double>(penta);
    ASSERT_TRUE(area == 0.0);
}

TEST(FigureTest, TrapEq) {
    Trapecia trap1(3.0, 5.0, 4.0);
    Trapecia trap2(3.0, 5.0, 4.0);
    ASSERT_TRUE(trap1 == trap2);
}

TEST(FigureTest, TrapNonEq) {
    Trapecia trap1(3.0, 5.0, 4.0);
    Trapecia trap2(3.0, 5.0, 5.0);
    ASSERT_TRUE(!(trap1 == trap2));
}

TEST(FigureTest, TrapEqZero) {
    Trapecia trap1(0.0, 0.0, 0.0);
    Trapecia trap2(0.0, 0.0, 0.0);
    ASSERT_TRUE(trap1 == trap2);
}

TEST(FigureTest, RombEq) {
    Romb romb1(4.0, 5.0);
    Romb romb2(4.0, 5.0);
    ASSERT_TRUE(romb1 == romb2);
}

TEST(FigureTest, RombNonEq) {
    Romb romb1(4.0, 5.0);
    Romb romb2(3.0, 6.0);
    ASSERT_TRUE(!(romb1 == romb2));
}

TEST(FigureTest, TrapCenter) {
    Trapecia trap(3.0, 5.0, 4.0);
    std::pair<double, double> center = trap.center();
    ASSERT_TRUE((center.first >= 2.160 && center.first <= 2.170) && (center.second <= 1.36 && center.second >= 1.3));
}

TEST(FigureTest, TrapCenterZero) {
    Trapecia trap(0.0, 0.0, 0.0);
    std::pair<double, double> center = trap.center();
    ASSERT_TRUE(center.first == 0.0 && center.second == 0.0);
}

TEST(FigureTest, PentaCenter) {
    Penta penta(3.0);
    std::pair<double, double> center = penta.center();
    ASSERT_TRUE((center.first > 6.06 && center.first < 6.07)&& (center.second <= 4.41 && center.second >= 4.40));
}
