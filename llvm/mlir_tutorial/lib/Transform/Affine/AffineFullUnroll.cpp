#include "lib/Transform/Affine/AffineFullUnroll.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Affine/LoopUtils.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"

namespace mlir {
namespace toy {

void AffineFullUnrollPass::runOnOperation() {
  getOperation().walk([&](affine::AffineForOp op) {
    if (llvm::failed(affine::loopUnrollFull(op))) {
      op.emitError("loop unrolling failed");
      signalPassFailure();
    }
  });
  return;
}

struct AffineFullUnrollPattern : public OpRewritePattern<affine::AffineForOp> {
  AffineFullUnrollPattern(mlir::MLIRContext *context)
      : OpRewritePattern<affine::AffineForOp>(context, 1) {}
  LogicalResult matchAndRewrite(affine::AffineForOp op,
                                PatternRewriter &rewriter) const override {
    return affine::loopUnrollFull(op);
  }
};

void AffineFullUnrollPassAsPatternRewrite::runOnOperation() {
  mlir::RewritePatternSet patterns(&getContext());
  patterns.add<AffineFullUnrollPattern>(&getContext());
  (void)applyPatternsGreedily(getOperation(), std::move(patterns));
}

} // namespace toy
} // namespace mlir
