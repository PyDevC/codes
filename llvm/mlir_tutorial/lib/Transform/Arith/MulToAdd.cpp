#include "lib/Transform/Arith/MulToAdd.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"

namespace mlir {
namespace toy {

struct PowerOfTwoExpand : public OpRewritePattern<arith::MulIOp> {
  PowerOfTwoExpand(mlir::MLIRContext *Context)
      : OpRewritePattern<arith::MulIOp>(Context, 2) {}
  LogicalResult matchAndRewrite(arith::MulIOp Op,
                                PatternRewriter &rewriter) const override {
    return success();
  }
};

struct PeelFromMul : public OpRewritePattern<arith::MulIOp> {
  PeelFromMul(mlir::MLIRContext *Context)
      : OpRewritePattern<arith::MulIOp>(Context, 1) {}
  LogicalResult matchAndRewrite(arith::MulIOp Op,
                                PatternRewriter &rewriter) const override {
    return success();
  }
};

void MulToAddPass::runOnOperation() {
  mlir::RewritePatternSet patterns(&getContext());
  patterns.add<PowerOfTwoExpand>(&getContext());
  patterns.add<PeelFromMul>(&getContext());
  (void)applyPatternsGreedily(getOperation(), std::move(patterns));
}

} // namespace toy
} // namespace mlir
