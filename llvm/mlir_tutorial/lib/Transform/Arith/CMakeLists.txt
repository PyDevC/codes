add_mlir_dialect_library(MulToAddPass
    MulToAdd.cpp
    ${PROJECT_SOURCE_DIR}/lib/Transform/Arith/

    LINK_LIBS PUBLIC
    MLIRArithDialect
    MLIRArithTransforms
    MLIRIR
    MLIRPass
    MLIRSupport
    MLIRTransforms
)

