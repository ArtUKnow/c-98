#include "../include/vowels.h"
#include <string>
#include <gtest/gtest.h>

// default
TEST(test_01, start_test) {
    std::string strs = "hello world";
    int result = vowels_counter(strs);
    std::cout<<result;
    ASSERT_TRUE(result == 3);
}
TEST(test_02, start_test) {
    std::string strs = "aeiouy";
    int result = vowels_counter(strs);
    std::cout<<result;
    ASSERT_TRUE(result == 6);
}
TEST(test_03, space_and_vowels) {
    std::string strs = "a e i o u l l l l";
    int result = vowels_counter(strs);
    std::cout<<result;
    ASSERT_TRUE(result == 5);
}
TEST(test_04, space_and_vowels) {
    std::string strs = "    ";
    int result = vowels_counter(strs);
    std::cout<<result;
    ASSERT_TRUE(result == 0);
}
TEST(test_05, space_and_vowels) {
    std::string strs = "   a a a ";
    int result = vowels_counter(strs);
    std::cout<<result;
    ASSERT_TRUE(result == 3);
}

TEST(test_06, space_and_vowels) {
    std::string strs = "                                       a                            g fg";
    int result = vowels_counter(strs);
    std::cout<<result;
    ASSERT_TRUE(result == 1);
}
TEST(test_07, numbers) {
    std::string strs = "1234";
    int result = vowels_counter(strs);
    std::cout<<result;
    ASSERT_TRUE(result == 0);
}
TEST(test_08, single_vowels) {
    std::string strs = "o";
    int result = vowels_counter(strs);
    std::cout<<result;
    ASSERT_TRUE(result == 1);
}
TEST(test_09, empty_vowels) {
    std::string strs = "";
    int result = vowels_counter(strs);
    std::cout<<result;
    ASSERT_TRUE(result == 0);
}
TEST(test_10, special_vowels) {
    std::string strs = "[aaa]1%^&^^@@@@";
    int result = vowels_counter(strs);
    std::cout<<result;
    ASSERT_TRUE(result == 3);
}