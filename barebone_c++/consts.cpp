#include <iostream>
#include "hit.h"

int main () {
    // Consts are variables that whose value cannot change
    const int age {10};

    // You can do both const int or int const (this is called east const)
    int const age1 {10};

    // Initialize consts from other variables; The type of age2 will be const int
    // instead of just int types are collectively called with const
    const int age2 {age};

    // Naming convention
    // If you are comming from C, people usually use uppercase with underscore as separator like TERMINAL_WINDOW
    // While C++ devs prefer to prefix 'k' before camelCase kTerminalWindow
    
    // Calling the const from header file
    std::cout << source << std::endl;
}

// Const arguments of a function are used for the complex types that tells the compiler, that value cannot be changed
int number( const int value) {
    return value;
}

// Return the Const type from the function; (for fundamental types you will get warning since it's ignored).
// You should not use const return when returning by value since it's stored in temporary object and then destroyed.
const int numberConst() {return 10;}
