set(LLVM_TARGET_DEFINITIONS PolyToStandard.td)
mlir_tablegen(PolyToStandard.h.inc -gen-pass-decls -name=PolyToStandard)
add_public_tablegen_target(PolyToStandardIncGen)

add_mlir_dialect_library(PolyToStandardPass
    PolyToStandard.cpp
    ${PROJECT_SOURCE_DIR}/lib/Conversion/PolyToStandard/

    DEPENDS
    PolyToStandardIncGen

    LINK_LIBS PUBLIC
    MLIRPass
    MLIRIR
    MLIRSupport
    MLIRTensorDialect
    MLIRArithDialect
    MLIRFuncDialect
    MLIRFuncTransforms
    MLIRSCFDialect
)
