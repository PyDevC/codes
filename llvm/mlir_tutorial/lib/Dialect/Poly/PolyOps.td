#ifndef LIB_DIALECT_POLY_POLYOPS_TD_
#define LIB_DIALECT_POLY_POLYOPS_TD_

include "PolyDialect.td"
include "PolyType.td"

include "mlir/IR/OpBase.td"
include "mlir/Interfaces/SideEffectInterfaces.td"

class Poly_BinOps<string mnemonic> : Op<Poly_Dialect, mnemonic, [Pure]>{
    let arguments = (ins Polynomial:$lhs, Polynomial:$rhs);
    let results = (outs Polynomial:$res);
    let assemblyFormat = "$lhs `,` $rhs attr-dict `:` `(` type($lhs) `,` type($rhs) `)` `->` type($res)";
}

def Poly_AddOps : Poly_BinOps<"add"> {
    let summary = "Addition between two Polynomials.";
}

def Poly_MulOps : Poly_BinOps<"mul"> {
    let summary = "Multiplication between two Polynomials.";
}

def Poly_SubOps : Poly_BinOps<"sub"> {
    let summary = "Subtraction between two Polynomials.";
}

def Poly_FromTensorOp : Op<Poly_Dialect, "from_tensor", [Pure]> {
    let summary = "Create Polynomial from a integer coefficient stored in a tensor.";
    let arguments = (ins TensorOf<[AnyInteger]>:$input);
    let results = (outs Polynomial:$res);
    let assemblyFormat = "$input attr-dict `:` type($input) `->` type($res)";
}

def Poly_EvalOp : Op<Poly_Dialect, "eval"> {
    let summary = "Evaluates a Polynomial at a given input value.";
    let arguments = (ins Polynomial:$input, AnyInteger:$point);
    let results = (outs AnyInteger:$res);
    let assemblyFormat = "$input`,` $point attr-dict `:` `(`type($input)`,` type($point)`)` `->` type($res)";
}

#endif // LIB_DIALECT_POLY_POLYOPS_TD_
