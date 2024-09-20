#include <iostream>
#include <string>
#include "lib.h"
#include "vowels.h"

int main() {
    std::string input = "lol check this";
    int count = vowels_counter(input);
    std::cout <<"c-98" << count << std::endl;
}
