#include "Parser.h"
#include <iostream>

int main(void) { 
    std::string input;
    Parser parser;
    do
    {
        std::cout << "read> ";
        std::cin >> input;
        parser.ParseExpression();
    } while (true);
    return 0; 
}
