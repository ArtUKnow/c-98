#include "../../include/vowels.h"
#include <iostream>
#include <string>

// тут думаю коментировать не надо :)
int vowels_counter(std::string& strs) {
    std::string vowels = "aeiouy";
    int count = 0;
    for (int i = 0; i < strs.length(); i++) {
        if ( vowels.find(strs[i] == 1)) {
            count++;
        }
    }
    return count;
}