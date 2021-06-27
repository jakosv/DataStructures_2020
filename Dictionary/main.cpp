#include "Dict.h"

#include <iostream>

int main() {
    Dict<char, int> m;
    m.setValue('c', 3);
    m.setValue('a', 4);
    std::cout << "Size: " << m.size() << std::endl;
    for (auto e : m) {
        std::cout << e.key << " " << e.value << std::endl;
    }
    m.removeKey('c');
    std::cout << "Size: " << m.size() << std::endl;
    for (auto e : m) {
        std::cout << e.key << " " << e.value << std::endl;
    }
    return 0;
}
