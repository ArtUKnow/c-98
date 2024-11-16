#include "../include/lists.h"
#include <gtest/gtest.h>

TEST(MyListTest, AddElementsInt) {
    // Arrange
    ListMemoryResource resource;
    MyList<int> int_list(&resource);

    // Act
    int_list.push_back(10);
    int_list.push_back(20);
    int_list.push_front(5);

    // Assert
    auto it = int_list.begin();
    EXPECT_EQ(*it, 5); ++it;
    EXPECT_EQ(*it, 10); ++it;
    EXPECT_EQ(*it, 20); ++it;
    EXPECT_EQ(it, int_list.end());
}
TEST(MyListTest, RemoveElementsInt) {
    // Arrange
    ListMemoryResource resource;
    MyList<int> int_list(&resource);
    int_list.push_back(10);
    int_list.push_back(20);
    int_list.push_front(5);

    // Act
    int_list.pop_back();
    int_list.pop_front();

    // Assert
    auto it = int_list.begin();
    EXPECT_EQ(*it, 10); ++it;
    EXPECT_EQ(it, int_list.end());
    EXPECT_EQ(int_list.get_size(), 1);
}

TEST(MyListTest, AddRemoveElementsComplex) {
    // Arrange
    ListMemoryResource resource;
    MyList<Complex> complex_list(&resource);
    complex_list.push_back({1, 1.1, "First"});
    complex_list.push_back({2, 2.2, "Second"});

    // Act
    complex_list.pop_back();

    // Assert
    auto it = complex_list.begin();
    EXPECT_EQ(it->name, "First");
    EXPECT_EQ(it->id, 1);
    EXPECT_EQ(it->value, 1.1);
    EXPECT_EQ(complex_list.get_size(), 1);
}

TEST(MyListTest, IterateElementsInt) {
    // Arrange
    ListMemoryResource resource;
    MyList<int> int_list(&resource);
    int_list.push_back(5);
    int_list.push_back(10);
    int_list.push_back(15);

    // Act
    int index = 0;
    for (auto it = int_list.begin(); it != int_list.end(); ++it) {
        // Assert
        if (index == 0) EXPECT_EQ(*it, 5);
        else if (index == 1) EXPECT_EQ(*it, 10);
        else if (index == 2) EXPECT_EQ(*it, 15);
        ++index;
    }
}

TEST(MyListTest, MemoryManagement) {
    // Arrange
    ListMemoryResource resource;
    MyList<int> int_list(&resource);

    // Act
    int_list.push_back(1);
    int_list.push_back(2);
    int_list.push_back(3);

    // Assert
    EXPECT_EQ(int_list.get_size(), 3);

    // Удаление всех элементов
    int_list.pop_front();
    int_list.pop_front();
    int_list.pop_front();

    // Проверка, что контейнер пуст
    EXPECT_EQ(int_list.get_size(), 0);
}
