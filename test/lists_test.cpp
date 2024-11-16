#include "../include/lists.h"
#include <gtest/gtest.h>
#include <string>

struct Complex {
    int a;
    double b;
    std::string c;

    Complex(int a, double b, const std::string& c) : a(a), b(b), c(c) {}

    bool operator==(const Complex& other) const {
        return a == other.a && b == other.b && c == other.c;
    }
};

TEST(MyListTests, PushBack_AddsElementsToEnd) {
    ListMemoryResource resource;
    MyList<int> list(&resource);

    list.push_back(10);
    list.push_back(20);

    MyList<int>::Iterator it = list.begin();
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(*it, 20);
    ++it;
    EXPECT_EQ(it, list.end());
}

TEST(MyListTests, PushFront_AddsElementsToFront) {
    ListMemoryResource resource;
    MyList<int> list(&resource);

    list.push_front(30);
    list.push_front(40);

    MyList<int>::Iterator it = list.begin();
    EXPECT_EQ(*it, 40);
    ++it;
    EXPECT_EQ(*it, 30);
    ++it;
    EXPECT_EQ(it, list.end());
}

TEST(MyListTests, PopBack_RemovesElementsFromEnd) {
    ListMemoryResource resource;
    MyList<int> list(&resource);
    list.push_back(50);
    list.push_back(60);

    list.pop_back();

    MyList<int>::Iterator it = list.begin();
    EXPECT_EQ(*it, 50);
    ++it;
    EXPECT_EQ(it, list.end());
}

TEST(MyListTests, PopFront_RemovesElementsFromFront) {
    ListMemoryResource resource;
    MyList<int> list(&resource);
    list.push_back(70);
    list.push_back(80);

    list.pop_front();

    MyList<int>::Iterator it = list.begin();
    EXPECT_EQ(*it, 80);
    ++it;
    EXPECT_EQ(it, list.end());
}

TEST(MyListTests, Size_ReturnsCorrectSize) {
    ListMemoryResource resource;
    MyList<int> list(&resource);

    list.push_back(90);
    list.push_back(100);
    list.push_back(110);

    EXPECT_EQ(list.get_size(), 3);
}

TEST(MyListTests, Iterator_WorksWithEmptyList) {
    ListMemoryResource resource;
    MyList<int> list(&resource);

    MyList<int>::Iterator it = list.begin();
    EXPECT_EQ(it, list.end());
}

TEST(MyListTests, ComplexType_SupportsPushAndPop) {
    ListMemoryResource resource;
    MyList<Complex> list(&resource);
    Complex obj1(1, 1.1, "First");
    Complex obj2(2, 2.2, "Second");

    list.push_back(obj1);
    list.push_back(obj2);
    list.pop_front();

    MyList<Complex>::Iterator it = list.begin();
    EXPECT_EQ(*it, obj2);
    ++it;
    EXPECT_EQ(it, list.end());
}

TEST(MyListTests, MemoryResource_ReusesMemory) {
    ListMemoryResource resource;
    MyList<int> list(&resource);

    list.push_back(1);
    list.pop_back();
    size_t before = resource.allocated_blocks.size();

    list.push_back(2);
    size_t after = resource.allocated_blocks.size();

    EXPECT_EQ(before, after);
}

TEST(MyListTests, Iterator_IteratesThroughAllElements) {
    ListMemoryResource resource;
    MyList<int> list(&resource);

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    std::vector<int> values;
    for (MyList<int>::Iterator it = list.begin(); it != list.end(); ++it) {
        values.push_back(*it);
    }

    std::vector<int> expected = {1, 2, 3};
    EXPECT_EQ(values, expected);
}

TEST(MyListTests, Destructor_CleansUpMemory) {
    ListMemoryResource* resource = new ListMemoryResource();
    {
        MyList<int> list(resource);
        list.push_back(1);
        list.push_back(2);
    }

    EXPECT_EQ(resource->allocated_blocks.size(), 0);
    delete resource;
}
