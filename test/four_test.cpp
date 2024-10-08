#include "../include/four.h"
#include <gtest/gtest.h>

TEST(FourTest, EqualTest) {
    Four num1("123");
    Four num2("123");
    ASSERT_TRUE(num1.isEqual(num2));
}

TEST(FourTest, GreaterTest) {
    Four num1("123");
    Four num2("101");
    ASSERT_TRUE(num1.isGreater(num2));
}

TEST(FourTest, LesserTest) {
    Four num1("101");
    Four num2("123");
    ASSERT_TRUE(num1.isLesser(num2));
}
