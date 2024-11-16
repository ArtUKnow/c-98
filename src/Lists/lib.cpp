#include "../../include/lists.h"
#include <iostream>
#include <cstring>

// === ListMemoryResource ===
void* ListMemoryResource::do_allocate(size_t bytes, size_t alignment) {
    void* ptr = ::operator new(bytes, std::align_val_t(alignment));
    allocated_blocks.push_back({ptr, bytes});
    return ptr;
}

void ListMemoryResource::do_deallocate(void* p, size_t bytes, size_t alignment) {
    auto it = std::find_if(allocated_blocks.begin(), allocated_blocks.end(),
                           [p](const Block& block) { return block.ptr == p; });

    if (it != allocated_blocks.end()) {
        allocated_blocks.erase(it);
    }

    ::operator delete(p, std::align_val_t(alignment));
}

bool ListMemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}

ListMemoryResource::~ListMemoryResource() {
    for (const auto& block : allocated_blocks) {
        ::operator delete(block.ptr);
    }
}

// === MyList ===
template <typename T>
MyList<T>::MyList(std::pmr::memory_resource* resource)
    : allocator(resource), head(nullptr), tail(nullptr), size(0) {}

template <typename T>
MyList<T>::~MyList() {
    while (head) {
        Node* temp = head;
        head = head->next;
        allocator.deallocate(temp, 1);
    }
}

template <typename T>
void MyList<T>::push_back(const T& value) {
    Node* node = allocator.allocate(1);
    allocator.construct(node, Node{value, tail, nullptr});

    if (tail) {
        tail->next = node;
    } else {
        head = node;
    }
    tail = node;
    ++size;
}

template <typename T>
void MyList<T>::push_front(const T& value) {
    Node* node = allocator.allocate(1);
    allocator.construct(node, Node{value, nullptr, head});

    if (head) {
        head->prev = node;
    } else {
        tail = node;
    }
    head = node;
    ++size;
}

template <typename T>
void MyList<T>::pop_back() {
    if (!tail) throw std::runtime_error("List is empty!");

    Node* node = tail;
    tail = tail->prev;

    if (tail) {
        tail->next = nullptr;
    } else {
        head = nullptr;
    }

    allocator.destroy(node);
    allocator.deallocate(node, 1);
    --size;
}

template <typename T>
void MyList<T>::pop_front() {
    if (!head) throw std::runtime_error("List is empty!");

    Node* node = head;
    head = head->next;

    if (head) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }

    allocator.destroy(node);
    allocator.deallocate(node, 1);
    --size;
}

template <typename T>
size_t MyList<T>::get_size() const {
    return size;
}

// === MyList::Iterator ===
template <typename T>
MyList<T>::Iterator::Iterator(Node* node) : current(node) {}

template <typename T>
T& MyList<T>::Iterator::operator*() {
    return current->value;
}

template <typename T>
typename MyList<T>::Iterator& MyList<T>::Iterator::operator++() {
    current = current->next;
    return *this;
}

template <typename T>
bool MyList<T>::Iterator::operator!=(const Iterator& other) const {
    return current != other.current;
}

template <typename T>
typename MyList<T>::Iterator MyList<T>::begin() {
    return Iterator(head);
}

template <typename T>
typename MyList<T>::Iterator MyList<T>::end() {
    return Iterator(nullptr);
}

// Instantiate templates
template class MyList<int>;
template class MyList<struct Complex>;
