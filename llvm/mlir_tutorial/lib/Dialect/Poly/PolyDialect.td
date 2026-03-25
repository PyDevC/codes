include "mlir/IR/DialectBase.td"

def Poly_Dialect : Dialect {
    let name = "poly";
    let summary = "Simple dialect";
    let description = [{
        The Poly Dialect defines types and operations for single-variable polynomials over integers.
    }];

    let cppNamespace = "::mlir::toy::poly";
    let useDefaultTypePrinterParser = 1;
}
