#include <gtest/gtest.h>


TEST(HelloTest, BasicAssertions) {
  // arrange 
  int first = 2;
  int second = 5;

  // act
  int sum = first + second;

  // assert
  EXPECT_EQ(sum, 7);
}
