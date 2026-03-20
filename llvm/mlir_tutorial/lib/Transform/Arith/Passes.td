#ifndef LIB_TRANSFORM_ARITH_PASSES_H_
#define LIB_TRANSFORM_ARITH_PASSES_H_

include "mlir/Pass/PassBase.td"

def MulToAdd : Pass<"arith-mul-to-add"> {
    let summary = "Convert Mul ops to Add by expanding the multiplication";
    let description = [{
        Convert Mul Ops to Add Ops by expanding the multiplication.
    }];
    let dependentDialects = ["mlir::arith::ArithDialect"];
}

#endif // LIB_TRANSFORM_ARITH_PASSES_H_
