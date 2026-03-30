#include "lib/Dialect/Poly/PolyDialect.h"

#include "lib/Dialect/Poly/PolyOps.h"
#include "lib/Dialect/Poly/PolyType.h"
#include "mlir/Dialect/Transform/Interfaces/TransformInterfaces.h"
#include "mlir/IR/Builders.h"
#include "llvm/ADT/TypeSwitch.h"

#include "lib/Dialect/Poly/PolyDialect.cpp.inc"

#define GET_TYPEDEF_CLASSES
#include "lib/Dialect/Poly/PolyType.cpp.inc"

#define GET_OP_CLASSES
#include "lib/Dialect/Poly/PolyOps.cpp.inc"

namespace mlir {
namespace toy {
namespace poly {

void PolyDialect::initialize() {
#define GET_TYPEDEF_LIST
  addTypes<
#include "lib/Dialect/Poly/PolyType.cpp.inc"
      >();

#define GET_OP_LIST
  addOperations<
#include "lib/Dialect/Poly/PolyOps.cpp.inc"
      >();
}

Operation *PolyDialect::materializeConstant(OpBuilder &builder, Attribute value,
                                            Type type, Location loc) {
  auto coeffs = llvm::dyn_cast<DenseIntElementsAttr>(value);
  if (!coeffs) {
    return nullptr;
  }
  return builder.create<ConstantOp>(loc, type, coeffs);
}

} // namespace poly
} // namespace toy
} // namespace mlir
