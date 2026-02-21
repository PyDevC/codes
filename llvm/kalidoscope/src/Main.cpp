#include "Lexer.h"
#include "Parser.h"

#include <iostream>

int main(void)
{
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();

    std::string input;
    Parser parser;
    llvm::ExitOnError ExitOnError;
    TheJIT = ExitOnError(llvm::orc::KaleidoscopeJIT::Create());
    InitializeModuleAndManagers();
    do {
        std::cout << "read> ";
        // This input method is not the most efficient but a patch to previous
        // whitespace skip bug
        if (!std::getline(std::cin, input))
            break;
        if (input == "exit")
            break;
        setoutput(input);
        input = "";
        parser.ParseMain();
    } while (true);
    getModule()->print(llvm::errs(), nullptr);
    return 0;
}
