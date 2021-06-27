#include "Dict.h"

#include <iostream>

int main() {
    Dict<char, int> m;
    m.setValue('c', 3);
    m.setValue('a', 4);
    for (auto e : m) {
        std::cout << e.key << " " << e.value;
    }
    return 0;
}
