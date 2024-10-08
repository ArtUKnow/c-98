#include "four.h"

void Four::checkValidDigit(unsigned char digit) const {
    if (digit > 3) {
        throw std::invalid_argument("Четвертичная цифра должна быть от 0 до 3");
    }
}

void Four::resizeArray(size_t newCapacity) {
    if (newCapacity > _capacity) {
        unsigned char* newDigits = new unsigned char[newCapacity];
        for (size_t i = 0; i < size; i++) {
            newDigits[i] = _digits[i];
        }
        delete[] _digits;
        _digits = newDigits;
        _capacity = newCapacity;
    }
}

Four::Four() {
    _digits = nullptr;
    _capacity = 0;
    size = 0;
}

Four::Four(const std::string& number) {
    size = number.size();
    _capacity = size;
    _digits = new unsigned char[_capacity];
    for (size_t i = 0; i < size; i++) {
        unsigned char digit = number[size - 1 - i] - '0';
        checkValidDigit(digit);
        _digits[i] = digit;
    }
}

Four::Four(const Four& other) {
    size = other.size;
    _capacity = other._capacity;
    _digits = new unsigned char[_capacity];
    for (size_t i = 0; i < size; i++) {
        _digits[i] = other._digits[i];
    }
}

Four::Four(Four&& other) noexcept {
    _digits = other._digits;
    _capacity = other._capacity;
    size = other.size;

    other._digits = nullptr;
    other._capacity = 0;
    other.size = 0;
}

Four::~Four() noexcept {
    delete[] _digits;
}

void Four::add(const Four& other) {
    size_t maxSize = (size > other.size) ? size : other.size;
    resizeArray(maxSize + 1);
    unsigned char carry = 0;

    for (size_t i = 0; i < maxSize; i++) {
        unsigned char this_digit= (i < size) ? _digits[i] : 0;
        unsigned char other_digit= (i < other.size) ? other._digits[i] : 0;
        unsigned char sum = this_digit+ other_digit+ carry;
        _digits[i] = sum % 4;
        carry = sum / 4;
    }

    if (carry > 0) {
        _digits[maxSize] = carry;
        size = maxSize + 1;
    } else {
        size = maxSize;
    }
}

void Four::subtract(const Four& other) {
    if (isLesser(other)) {
        throw std::invalid_argument("Результат будет отрицательным");
    }

    unsigned char borrow = 0;
    for (size_t i = 0; i < size; i++) {
        unsigned char this_digit= _digits[i];
        unsigned char other_digit= (i < other.size) ? other._digits[i] : 0;

        if (this_digit< other_digit+ borrow) {
            _digits[i] = this_digit+ 4 - other_digit- borrow;
            borrow = 1;
        } else {
            _digits[i] = this_digit- other_digit- borrow;
            borrow = 0;
        }
    }
}

bool Four::isEqual(const Four& other) const {
    if (size != other.size) return false;
    for (size_t i = 0; i < size; i++) {
        if (_digits[i] != other._digits[i]) return false;
    }
    return true;
}

bool Four::isGreater(const Four& other) const {
    if (size > other.size) return true;
    if (size < other.size) return false;

    for (size_t i = size; i > 0; i--) {
        if (_digits[i - 1] > other._digits[i - 1]) return true;
        if (_digits[i - 1] < other._digits[i - 1]) return false;
    }
    return false;
}

bool Four::isLesser(const Four& other) const {
    return !isGreater(other) && !isEqual(other);
}

void Four::print() const {
    for (size_t i = size; i > 0; i--) {
        std::cout << (int)_digits[i - 1];
    }
    std::cout << std::endl;
}
