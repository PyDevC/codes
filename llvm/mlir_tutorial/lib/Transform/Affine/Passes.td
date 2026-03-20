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

def AffineFullUnrollPatternRewrite : Pass<"affine-full-unroll-rewrite"> {
    let summary = "Fully Unroll all affine loops using pattern rewriter engine";
    let description = [{
        Full Unroll all affine loops using pattern rewriter engine.
    }];
    let dependentDialects = ["mlir::affine::AffineDialect"];
}

#endif // LIB_TRANSFORM_AFFINE_PASSES_H_
