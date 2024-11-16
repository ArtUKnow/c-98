#include "./include/lists.h"
#include <iostream>
#include <string>

int main() {
    ListMemoryResource resource;

    MyList<int> intList(&resource);
    intList.push_back(1);
    intList.push_back(2);
    intList.push_back(3);

    std::cout << "Int List:" << std::endl;
    for (auto& value : intList) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    MyList<Complex> complexList(&resource);
    complexList.push_back(Complex(1, 1.1, "One"));
    complexList.push_back(Complex(2, 2.2, "Two"));

    std::cout << "Complex List:" << std::endl;
    for (auto& value : complexList) {
        std::cout << "{ " << value.a << ", " << value.b << ", " << value.c << " } ";
    }
    std::cout << std::endl;

    return 0;
}
