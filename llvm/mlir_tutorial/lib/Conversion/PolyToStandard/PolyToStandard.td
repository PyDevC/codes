#ifndef LIB_CONVERSION_POLYTOSTANDARD_POLYTOSTANDARD_TD_
#define LIB_CONVERSION_POLYTOSTANDARD_POLYTOSTANDARD_TD_

include "mlir/Pass/PassBase.td"
 
def PolyToStandard : Pass<"poly-to-standard"> {
    let summary = "Lower Poly Dialect to standard MLIR.";
    let dependentDialects = [
        "mlir::arith::ArithDialect",
        "mlir::toy::poly::PolyDialect",
        "mlir::tensor::TensorDialect",
        "mlir::scf::SCFDialect",
    ];
}

#endif // LIB_CONVERSION_POLYTOSTANDARD_POLYTOSTANDARD_TD_
