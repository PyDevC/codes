add_mlir_dialect_library(AffineFullUnrollPass
    AffineFullUnroll.cpp
    ${PROJECT_SOURCE_DIR}/lib/Transform/Affine/

    LINK_LIBS PUBLIC
    MLIRAffineDialect
    MLIRAffineTransforms
    MLIRIR
    MLIRPass
    MLIRSupport
    MLIRTransforms
)

