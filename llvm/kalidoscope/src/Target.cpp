#include "Target.h"
#include "Parser.h"

void InitAllTargets()
{
    llvm::InitializeAllTargetInfos();
    llvm::InitializeAllTargets();
    llvm::InitializeAllTargetMCs();
    llvm::InitializeAllAsmParsers();
    llvm::InitializeAllAsmPrinters();
}

int BuildToTarget(std::string filename)
{
    auto TargetTriple = llvm::sys::getDefaultTargetTriple();
    std::unique_ptr<llvm::Module> Module = getModule();
    Module->setTargetTriple(llvm::Triple(TargetTriple));

    std::string Errors;

    auto Target =
      llvm::TargetRegistry::lookupTarget(Module->getTargetTriple(), Errors);

    if (!Target) {
        llvm::errs() << Errors;
        return 1;
    }

    auto CPU = "generic";
    auto Features = "";
    llvm::TargetOptions TargetOpt;

    auto TargetMachine =
        Target->createTargetMachine(llvm::Triple(TargetTriple), CPU, Features,
                                    TargetOpt, llvm::Reloc::PIC_);

    Module->setDataLayout(TargetMachine->createDataLayout());

    auto Filename = filename;
    std::error_code ErrorCode;
    llvm::raw_fd_ostream dest(Filename, ErrorCode, llvm::sys::fs::OF_None);

    if (ErrorCode) {
        llvm::errs() << "Could not open file" << ErrorCode.message();
        return 1;
    }

    llvm::legacy::PassManager Pass;
    auto FileType = llvm::CodeGenFileType::ObjectFile;

    if (TargetMachine->addPassesToEmitFile(Pass, dest, nullptr, FileType)) {
        llvm::errs() << "Target Machine can't emit a file of this type.";
        return 1;
    }

    Pass.run(*Module);
    dest.flush();

    llvm::outs() << "Object file out " << Filename << "\n";

    return 0;
}
