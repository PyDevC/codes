set(LLVM_TARGET_DEFINITIONS PolyDialect.td)
mlir_tablegen(PolyDialect.h.inc -gen-dialect-decls -name=Poly)
mlir_tablegen(PolyDialect.cpp.inc -gen-dialect-defs -name=Poly)
add_public_tablegen_target(PolyDialectIncGen)

set(LLVM_TARGET_DEFINITIONS PolyType.td)
mlir_tablegen(PolyType.h.inc -gen-typedef-decls -name=Poly)
mlir_tablegen(PolyType.cpp.inc -gen-typedef-defs -name=Poly)
add_public_tablegen_target(PolyTypeIncGen)

add_mlir_dialect_library(PolyDialect
    PolyDialect.cpp
    ${PROJECT_SOURCE_DIR}/lib/Dialect/Poly/

    DEPENDS
    PolyDialectIncGen
    PolyTypeIncGen

    LINK_LIBS PUBLIC
    MLIRDialect
    MLIRIR
    MLIRSupport
)
