#include "../../include/vowels.h"
#include <iostream>
#include <string>

int vowels_counter(std::string strs) {
    std::string vowels = "aeiouyAEIOUY"; // забыл про заглавные
    int count = 0;
    for (int i = 0; i < strs.length(); i++) {
        for (int j = 0; j < vowels.length(); j++) {
            if (strs[i] == vowels[j]) {
                count++;
                break;
            }
        }
    }
    return count;
}
