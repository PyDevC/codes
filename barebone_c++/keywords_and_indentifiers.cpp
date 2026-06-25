// They Keywords are reserved that have special meanings, you can't use them as
// indentifiers. But there are some special indentifiers that have special
// meaning is specific scenario but can be used as normal indentifiers in other
// case.
//
// Number of keywords as C++ standards increase
// C++11: 73
// C++13: 73
// C++17: 73
// C++20: 81
// C++23: 73
// C++26: don't know yet

#include <iostream>

int main() {
    // you can even do
    int override = 10;
    std::cout << override << std::endl;
    return 0;
}
