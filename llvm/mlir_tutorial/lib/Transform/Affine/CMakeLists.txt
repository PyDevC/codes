set(LLVM_TARGET_DEFINITIONS Passes.td)
mlir_tablegen(Passes.h.inc -gen-pass-decls -name=Affine)
add_public_tablegen_target(AffinePassIncGen)

add_mlir_dialect_library(AffineFullUnrollPass
    AffineFullUnroll.cpp
    ${PROJECT_SOURCE_DIR}/lib/Transform/Affine/

    DEPENDS
    AffinePassIncGen

    LINK_LIBS PUBLIC
    MLIRAffineDialect
    MLIRAffineTransforms
    MLIRIR
    MLIRPass
    MLIRSupport
    MLIRTransforms
)
