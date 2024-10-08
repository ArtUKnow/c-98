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
    virtual ~Four() noexcept;
    void add(const Four& other);
    void subtract(const Four& other);
    bool isEqual(const Four& other) const;
    bool isGreater(const Four& other) const;
    bool isLesser(const Four& other) const;
    void print() const;

private:
    unsigned char* digits;
    size_t size; 
    void check_valid_quaternary_digit(unsigned char digit) const;
};

#endif 
