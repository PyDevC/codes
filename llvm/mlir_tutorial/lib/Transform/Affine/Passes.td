#ifndef LIB_TRANSFORM_AFFINE_PASSES_H_
#define LIB_TRANSFORM_AFFINE_PASSES_H_

include "mlir/Pass/PassBase.td"

def AffineFullUnroll : Pass<"affine-full-unroll"> {
    let summary = "Fully Unroll all affine loops";
    let description = [{
        Full Unroll all affine loops.
    }];
    let dependentDialects = ["mlir::affine::AffineDialect"];
}

#endif // LIB_TRANSFORM_AFFINE_PASSES_H_
