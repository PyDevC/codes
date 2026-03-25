#include "lib/Dialect/Poly/PolyDialect.h"

#include "lib/Dialect/Poly/PolyOps.h"
#include "lib/Dialect/Poly/PolyType.h"
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

} // namespace poly
} // namespace toy
} // namespace mlir
