#include "lib/Dialect/Poly/PolyDialect.h"

#include "lib/Dialect/Poly/PolyDialect.cpp.inc"
#include "lib/Dialect/Poly/PolyType.h"
#include "mlir/IR/Builders.h"
#include "llvm/ADT/TypeSwitch.h"

#define GET_TYPEDEF_CLASSES
#include "lib/Dialect/Poly/PolyType.cpp.inc"

namespace mlir {
namespace toy {
namespace poly {

void PolyDialect::initialize() {
  addTypes<
#define GET_TYPEDEF_LIST
#include "lib/Dialect/Poly/PolyType.cpp.inc"
      >();
}

} // namespace poly
} // namespace toy
} // namespace mlir
