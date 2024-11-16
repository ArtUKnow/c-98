#ifndef LIB_H
#define LIB_H

#include <memory_resource>
#include <iostream>
#include <list>
#include <cstddef>
#include <string>

// Структура Complex
struct Complex {
    int a;
    double b;
    std::string c;

    Complex(int a, double b, const std::string& c) : a(a), b(b), c(c) {}

    bool operator==(const Complex& other) const {
        return a == other.a && b == other.b && c == other.c;
    }
};

// Собственная memory_resource, сохраняющая информацию об аллокациях
class ListMemoryResource : public std::pmr::memory_resource {
public:
    ListMemoryResource() = default;
    ~ListMemoryResource();

protected:
    void* do_allocate(size_t bytes, size_t alignment) override;
    void do_deallocate(void* p, size_t bytes, size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

private:
    struct MemoryBlock {
        void* ptr;
        size_t size;
    };

    std::list<MemoryBlock> allocated_blocks;
};

// Шаблонный класс итератора
template <typename T>
class MyListIterator {
public:
    explicit MyListIterator(typename T::Node* node) : current(node) {}

    typename T::value_type& operator*() { return current->value; }
    MyListIterator& operator++() { current = current->next; return *this; }
    MyListIterator operator++(int) { MyListIterator temp = *this; current = current->next; return temp; }
    bool operator!=(const MyListIterator& other) const { return current != other.current; }

private:
    typename T::Node* current;
};

// Шаблонный класс двусвязного списка
template <typename T>
class MyList {
    struct Node {
        T value;
        Node* next = nullptr;
        Node* prev = nullptr;

        explicit Node(const T& value) : value(value) {}
    };

public:
    using value_type = T;
    using iterator = MyListIterator<MyList<T>>;

    explicit MyList(ListMemoryResource* resource);
    ~MyList();

    void push_back(const T& value);
    void push_front(const T& value);
    void pop_back();
    void pop_front();

    iterator begin() const { return iterator(head); }
    iterator end() const { return iterator(nullptr); }

    size_t get_size() const { return size; }

private:
    Node* head = nullptr;
    Node* tail = nullptr;
    size_t size = 0;
    std::pmr::polymorphic_allocator<Node> allocator;
};

#endif // LIB_H
