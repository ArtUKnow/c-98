#ifndef LIB_H
#define LIB_H

#include <memory_resource>
#include <list>
#include <iterator>
#include <stdexcept>

class ListMemoryResource : public std::pmr::memory_resource {
private:
    struct Block {
        void* ptr;
        size_t size;
    };

    std::list<Block> allocated_blocks;

protected:
    void* do_allocate(size_t bytes, size_t alignment) override;
    void do_deallocate(void* p, size_t bytes, size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

public:
    ~ListMemoryResource();
};

template <typename T>
class MyList {
private:
    struct Node {
        T value;
        Node* prev;
        Node* next;
    };

    std::pmr::polymorphic_allocator<Node> allocator;
    Node* head;
    Node* tail;
    size_t size;

public:
    explicit MyList(std::pmr::memory_resource* resource = std::pmr::get_default_resource());
    ~MyList();

    void push_back(const T& value);
    void push_front(const T& value);
    void pop_back();
    void pop_front();

    size_t get_size() const;

    class Iterator {
    private:
        Node* current;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(Node* node);
        T& operator*();
        Iterator& operator++();
        bool operator!=(const Iterator& other) const;
    };

    Iterator begin();
    Iterator end();
};

#endif // LIB_H
