#include "../../include/lists.h"

// Реализация ListMemoryResource
ListMemoryResource::~ListMemoryResource() {
    for (auto& block : allocated_blocks) {
        ::operator delete(block.ptr, block.size);
    }
    allocated_blocks.clear();
}

void* ListMemoryResource::do_allocate(size_t bytes, size_t alignment) {
    void* ptr = ::operator new(bytes, std::align_val_t(alignment));
    allocated_blocks.push_back({ptr, bytes});
    return ptr;
}

void ListMemoryResource::do_deallocate(void* p, size_t bytes, size_t alignment) {
    for (auto it = allocated_blocks.begin(); it != allocated_blocks.end(); ++it) {
        if (it->ptr == p) {
            allocated_blocks.erase(it);
            break;
        }
    }
    ::operator delete(p, std::align_val_t(alignment));  // Правильное использование delete
}

bool ListMemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}

// Реализация MyList
template <typename T>
MyList<T>::MyList(ListMemoryResource* resource)
    : allocator(std::pmr::polymorphic_allocator<Node>(resource)) {}

template <typename T>
MyList<T>::~MyList() {
    while (head) {
        Node* next = head->next;
        std::allocator_traits<decltype(allocator)>::destroy(allocator, head);
        allocator.deallocate(head, 1);
        head = next;
    }
}

template <typename T>
void MyList<T>::push_back(const T& value) {
    Node* node = allocator.allocate(1);
    std::allocator_traits<decltype(allocator)>::construct(allocator, node, value);
    if (!tail) {
        head = tail = node;
    } else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    ++size;
}

template <typename T>
void MyList<T>::push_front(const T& value) {
    Node* node = allocator.allocate(1);
    std::allocator_traits<decltype(allocator)>::construct(allocator, node, value);
    if (!head) {
        head = tail = node;
    } else {
        head->prev = node;
        node->next = head;
        head = node;
    }
    ++size;
}

template <typename T>
void MyList<T>::pop_back() {
    if (!tail) return;
    Node* node = tail;
    tail = tail->prev;
    if (tail) {
        tail->next = nullptr;
    } else {
        head = nullptr;
    }
    std::allocator_traits<decltype(allocator)>::destroy(allocator, node);
    allocator.deallocate(node, 1);
    --size;
}

template <typename T>
void MyList<T>::pop_front() {
    if (!head) return;
    Node* node = head;
    head = head->next;
    if (head) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }
    std::allocator_traits<decltype(allocator)>::destroy(allocator, node);
    allocator.deallocate(node, 1);
    --size;
}

// Эксплицитная инстанциация шаблонов
template class MyList<int>;
template class MyList<Complex>;
