#include "lib/Dialect/Poly/PolyOps.h"

#include "mlir/Dialect/CommonFolders.h"
#include "llvm/Support/Debug.h"

namespace mlir {
namespace toy {
namespace poly {

OpFoldResult ConstantOp::fold(ConstantOp::FoldAdaptor adapter) {
  return adapter.getCoefficient();
}

OpFoldResult AddOp::fold(AddOp::FoldAdaptor adapter) {
  return constFoldBinaryOp<IntegerAttr, APInt, void>(
      adapter.getOperands(), [&](APInt a, APInt b) { return a + b; });
}

OpFoldResult SubOp::fold(SubOp::FoldAdaptor adapter) {
  return constFoldBinaryOp<IntegerAttr, APInt, void>(
      adapter.getOperands(), [&](APInt a, APInt b) { return a - b; });
}

OpFoldResult MulOp::fold(MulOp::FoldAdaptor adapter) {
  auto lhs = llvm::cast<DenseIntElementsAttr>(adapter.getOperands()[0]);
  auto rhs = llvm::cast<DenseIntElementsAttr>(adapter.getOperands()[1]);
  auto degree =
      llvm::cast<PolynomialType>(getResult().getType()).getDecimalBound();
  auto maxIndex = lhs.size() + rhs.size() - 1;

  llvm::SmallVector<APInt, 8> result;
  result.reserve(maxIndex);
  for (int i = 0; i < maxIndex; ++i) {
    result.push_back(APInt((*lhs.begin()).getBitWidth(), 0));
  }

  int i = 0;
  for (auto lhsIt = lhs.value_begin<APInt>(); lhsIt != lhs.value_end<APInt>();
       ++lhsIt) {
    int j = 0;
    for (auto rhsIt = rhs.value_begin<APInt>(); rhsIt != rhs.value_end<APInt>();
         ++rhsIt) {
      result[(i + j) % degree] += *rhsIt * (*lhsIt);
    }
  }

  return DenseIntElementsAttr::get(
      RankedTensorType::get(static_cast<int64_t>(result.size()),
                            IntegerType::get(getContext(), 32)),
      result);
}

OpFoldResult FromTensorOp::fold(FromTensorOp::FoldAdaptor adapter){
    return llvm::dyn_cast<DenseIntElementsAttr>(adapter.getInput());
}

} // namespace poly
} // namespace toy
} // namespace mlir
