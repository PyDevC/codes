#include "Lexer.h"
#include "Parser.h"

#include <iostream>

int main(void)
{
    std::string input;
    Parser parser;
    do {
        std::cout << "read> ";
        // This input method is not the most efficient but a patch to previous
        // whitespace skip bug
        if (!std::getline(std::cin, input))
            break;
        if (input == "exit")
            break;
        setoutput(input);
        parser.ParseMain();
    } while (true);
    return 0;
}
