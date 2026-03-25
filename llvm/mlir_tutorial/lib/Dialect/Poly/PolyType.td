#ifndef LIB_DIALECT_POLY_POLYTYPE_TD_
#define LIB_DIALECT_POLY_POLYTYPE_TD_

include "PolyDialect.td"
include "mlir/IR/AttrTypeBase.td"

class Poly_Type<string name, string typeMnemonic> : TypeDef<Poly_Dialect, name> {
    let mnemonic = typeMnemonic;
}

def Polynomial : Poly_Type<"Polynomial", "poly"> {
    let summary = "A Polynomial with u32 coefficients.";
    let description = [{
        A Polynomial type with single coefficient integer in a single variable polynomial ring.
    }];

    let parameters = (ins "int":$decimalBound);
    let assemblyFormat = "`<` $decimalBound `>`";
}

#endif // LIB_DIALECT_POLY_POLYTYPE_TD_
