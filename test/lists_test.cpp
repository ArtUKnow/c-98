#include "../include/lists.h"
#include <gtest/gtest.h>

TEST(MyListTest, IntOperations) {
    ListMemoryResource resource;
    MyList<int> list(&resource);
    list.push_back(1);
    list.push_back(2);
    list.push_front(0);
    ASSERT_EQ(list.get_size(), 3);
    MyList<int>::iterator it = list.begin();
    ASSERT_EQ(*it, 0);
    ++it;
    ASSERT_EQ(*it, 1);
    ++it;
    ASSERT_EQ(*it, 2);
}

TEST(MyListTest, ComplexOperations) {
    ListMemoryResource resource;
    MyList<Complex> list(&resource);
    Complex c1(1, 2.0, "one");
    Complex c2(2, 3.0, "two");
    Complex c3(3, 4.0, "three");
    list.push_back(c1);
    list.push_back(c2);
    list.push_front(c3);
    ASSERT_EQ(list.get_size(), 3);
    MyList<Complex>::iterator it = list.begin();
    ASSERT_EQ(*it, c3);
    ++it;
    ASSERT_EQ(*it, c1);
    ++it;
    ASSERT_EQ(*it, c2);
}

TEST(MyListTest, IteratorOperations) {
    ListMemoryResource resource;
    MyList<int> list(&resource);
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    MyList<int>::iterator it = list.begin();

    ASSERT_EQ(*it, 1);
    ++it;
    ASSERT_EQ(*it, 2);
    ++it;
    ASSERT_EQ(*it, 3);
    ++it;
    ASSERT_EQ(it, list.end());
}

TEST(MyListTest, PopOperations) {
    ListMemoryResource resource;
    MyList<int> list(&resource);
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.pop_back();
    list.pop_front();

    ASSERT_EQ(list.get_size(), 1);
    MyList<int>::iterator it = list.begin();
    ASSERT_EQ(*it, 2);
}

TEST(MyListTest, EmptyListOperations) {
    ListMemoryResource resource;
    MyList<int> list(&resource);
    ASSERT_EQ(list.get_size(), 0);
    list.pop_back();
    list.pop_front();
    ASSERT_EQ(list.get_size(), 0);
}