#include <iostream>
#include <string>
#include "four.h"

int main() {
    Four num1("123");
    Four num2("101");
    
    num1.add(num2);
    std::cout << "SUM";
    num1.print();

    num1.subtract(num2);
    std::cout << "SUB";
    num1.print();

    bool equal = num1.isEqual(num2);
    std::cout << "EQ" << (equal ? "Да" : "Нет") << std::endl;

    bool greater = num1.isGreater(num2);
    std::cout << "GR: " << (greater ? "Да" : "Нет") << std::endl;

    return 0;
}
