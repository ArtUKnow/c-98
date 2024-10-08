#include "../include/four.h"
#include <gtest/gtest.h>

TEST(FourTest, EqualTest) {
    Four num1("123");
    Four num2("123");
    bool result = num1.isEqual(num2);
    ASSERT_TRUE(result);
}

TEST(FourTest, GreaterTest) {
    Four num1("123");
    Four num2("101");
    bool result = num1.isGreater(num2);
    ASSERT_TRUE(result);
}

TEST(FourTest, LesserTest) {
    Four num1("101");
    Four num2("123");
    bool result = num1.isLesser(num2);
    ASSERT_TRUE(result);
}

TEST(FourTest, ZeroNumTest) {
    Four num1("001");
    Four num2("0123");
    bool result = num1.isLesser(num2);
    ASSERT_TRUE(result);
}

TEST(FourTest, AdditionTest) {
    Four num1("123");
    Four num2("231");
    Four result = num1.add(num2);
    ASSERT_TRUE(result.isEqual("1020"));
}
