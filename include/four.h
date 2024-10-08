#ifndef FOUR_H
#define FOUR_H

#include <iostream>
#include <stdexcept>
#include <string>

class Four {
public:
    Four();
    Four(const std::string& number);
    Four(const Four& other);
    Four(Four&& other) noexcept;
    ~Four() noexcept;

    void add(const Four& other);
    void subtract(const Four& other);

    bool isEqual(const Four& other) const;
    bool isGreater(const Four& other) const;
    bool isLesser(const Four& other) const;

    void print() const;

private:
    unsigned char* _digits;
    size_t _capacity;
    size_t size;

    void checkValidDigit(unsigned char digit) const;
    void resizeArray(size_t newCapacity);
};

#endif
