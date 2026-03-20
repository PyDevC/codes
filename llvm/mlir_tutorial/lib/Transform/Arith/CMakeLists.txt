set(LLVM_TARGET_DEFINITIONS Passes.td)
mlir_tablegen(Passes.h.inc -gen-pass-decls -name=Arith)
add_public_tablegen_target(ArithPassIncGen)

add_mlir_dialect_library(MulToAddPass
    MulToAdd.cpp
    ${PROJECT_SOURCE_DIR}/lib/Transform/Arith/

    DEPENDS
    ArithPassIncGen

    LINK_LIBS PUBLIC
    MLIRArithDialect
    MLIRArithTransforms
    MLIRIR
    MLIRPass
    MLIRSupport
    MLIRTransforms
)
