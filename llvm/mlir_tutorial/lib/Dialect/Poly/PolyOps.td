#ifndef LIB_DIALECT_POLY_POLYOPS_TD_
#define LIB_DIALECT_POLY_POLYOPS_TD_

include "PolyDialect.td"
include "PolyType.td"

include "mlir/IR/OpBase.td"
include "mlir/IR/BuiltinAttributes.td"
include "mlir/Interfaces/SideEffectInterfaces.td"

def PolyORContainer : TypeOrValueSemanticsContainer<Polynomial, "poly-or-container">;

class Poly_BinOps<string mnemonic> : Op<Poly_Dialect, mnemonic, [Pure, ElementwiseMappable, SameOperandsAndResultElementType]>{
    let arguments = (ins PolyORContainer:$lhs, PolyORContainer:$rhs);
    let results = (outs PolyORContainer:$res);
    let assemblyFormat = "$lhs `,` $rhs attr-dict `:` `(` type($lhs) `,` type($rhs) `)` `->` type($res)";
    let hasFolder = 1;
}

def Poly_AddOp : Poly_BinOps<"add"> {
    let summary = "Addition between two Polynomials.";
}

def Poly_MulOp : Poly_BinOps<"mul"> {
    let summary = "Multiplication between two Polynomials.";
}

def Poly_SubOp : Poly_BinOps<"sub"> {
    let summary = "Subtraction between two Polynomials.";
}

def Poly_FromTensorOp : Op<Poly_Dialect, "from_tensor", [Pure]> {
    let summary = "Create Polynomial from a integer coefficient stored in a tensor.";
    let arguments = (ins TensorOf<[AnyInteger]>:$input);
    let results = (outs Polynomial:$res);
    let assemblyFormat = "$input attr-dict `:` type($input) `->` type($res)";
    let hasFolder = 1;
}

def Poly_EvalOp : Op<Poly_Dialect, "eval"> {
    let summary = "Evaluates a Polynomial at a given input value.";
    let arguments = (ins Polynomial:$input, AnyInteger:$point);
    let results = (outs AnyInteger:$res);
    let assemblyFormat = "$input`,` $point attr-dict `:` `(`type($input)`,` type($point)`)` `->` type($res)";
}

def Poly_ConstantOp : Op<Poly_Dialect, "constant", [Pure, ConstantLike]> {
    let summary = "Define a constant polynomial via an attribute.";
    let arguments = (ins AnyIntElementsAttr:$coefficient);
    let results = (outs Polynomial:$constant);
    let assemblyFormat = "$coefficient attr-dict `:` type($constant)";
    let hasFolder = 1;
}

#endif // LIB_DIALECT_POLY_POLYOPS_TD_
