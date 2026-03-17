#ifndef LIB_TRANSFORM_ARITH_MULTOADD_H_
#define LIB_TRANSFORM_ARITH_MULTOADD_H_

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Pass/Pass.h"

namespace mlir {
namespace toy {

class MulToAddPass
    : public PassWrapper<MulToAddPass, OperationPass<mlir::func::FuncOp>> {

  void runOnOperation() override;
  mlir::StringRef getArgument() const final { return "arith-mul-to-add"; }
    mlir::StringRef getDescription() const final { return "Convert Mul ops to Add ops expanding multiplications as additions"; }
};

} // namespace toy
} // namespace mlir

#endif // LIB_TRANSFORM_ARITH_MULTOADD_H_
