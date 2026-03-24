set(LLVM_TARGET_DEFINITIONS PolyDialect.td)
mlir_tablegen(PolyDialect.h.inc -gen-dialect-decls -name=Poly)
mlir_tablegen(PolyDialect.cpp.inc -gen-dialect-defs -name=Poly)
add_public_tablegen_target(PolyDialectIncGen)

add_mlir_dialect_library(PolyDialect
    PolyDialect.cpp
    ${PROJECT_SOURCE_DIR}/lib/Dialect/Poly/

    DEPENDS
    PolyDialectIncGen

    LINK_LIBS PUBLIC
    MLIRDialect
    MLIRIR
    MLIRSupport
)
