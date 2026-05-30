#include <iostream>

// iostream is contains all nuts and bolts required for i/o 

// std::cout (character output) is used to output the character to the console.
// for all simple data types it can easy print the exact character required to 
// represent. It uses << operator to pass in the std::cout function;

int main() {
    std::cout << "Hello, World!"; // Printing string on console

    std::cout << 5; // Printing literal number on console
    
    int x {1};
    std::cout << x; // Printing int variable on console
    
    float y {1.2f};
    std::cout << y; // Printing float variable on console

    // This is example of string concat on std::cout (it is different from 
    // general concat)
    std::cout << "Hello" << ", " << "World!"; // Printing multiple strings
    
    //  As observed there are no new lines what so ever
    // To add newline we add std::endl
    std::cout << "The End" << std::endl;

    // std::cout prints the data in buffers, first the data is entered to 
    // buffer and waited it its fill or until buffer is flushed.
    // When Buffer is flushed the data is printed to console.
    // std::endl enforces buffer to flush and create new buffer for new 
    // characters next time the std::cout is called. If you program is crashed,
    // aborted, or paused before the buffer is flushed, then the output will 
    // not get displayed.

    // cin is pretty similar like cout 
    int z{};
    std::cin >> z;
    std::cout << "value of z is " << z << std::endl;

    // you can also take multiple inputs at once
    std::cin >> x >> y;
    std::cout << "value of x and y is " << x  << "and" << y << std::endl;

    return 0;
}
