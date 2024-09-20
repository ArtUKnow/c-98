#include "../include/vowels.h"
#include <string>
#include <gtest/gtest.h>

TEST(test_01, basic_test_set) {
    std::string strs = "hello world";
    int result = vowels_counter(strs);
    std::cout<<result;
    ASSERT_TRUE(result == 3);
}
TEST(test_02, basic_test_set) {
    std::string strs = "aeiouy";
    int result = vowels_counter(strs);
    std::cout<<result;
    ASSERT_TRUE(result == 6);
}
TEST(test_03, basic_test_set) {
    std::string strs = "a e i o u l l l l";
    int result = vowels_counter(strs);
    std::cout<<result;
    ASSERT_TRUE(result == 5);
}
TEST(test_04, basic_test_set) {
    std::string strs = "    ";
    int result = vowels_counter(strs);
    std::cout<<result;
    ASSERT_TRUE(result == 0);
}
TEST(test_05, basic_test_set) {
    std::string strs = "   a a a ";
    int result = vowels_counter(strs);
    std::cout<<result;
    ASSERT_TRUE(result == 3);
}

TEST(test_06, basic_test_set) {
    std::string strs = "                                       a                            g fg";
    int result = vowels_counter(strs);
    std::cout<<result;
    ASSERT_TRUE(result == 1);
}
TEST(test_07, basic_test_set) {
    std::string strs = "1234";
    int result = vowels_counter(strs);
    std::cout<<result;
    ASSERT_TRUE(result == 0);
}