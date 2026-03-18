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
    mlir::Value Left = Op.getOperand(0);
    mlir::Value Right = Op.getOperand(1);

    auto RightDefiningOp = Right.getDefiningOp<arith::ConstantIntOp>();
    if (!RightDefiningOp) {
      return failure();
    }
    int64_t Value = RightDefiningOp.value();
    bool is_power_of_two = ((Value & (Value - 1)) == 0);
    if (!is_power_of_two) {
      return failure();
    }
    arith::ConstantOp newConstant = rewriter.create<arith::ConstantOp>(
        RightDefiningOp.getLoc(),
        rewriter.getIntegerAttr(Right.getType(), Value / 2));
    arith::MulIOp newMul =
        rewriter.create<arith::MulIOp>(Op.getLoc(), Left, newConstant);
    arith::AddIOp newAdd =
        rewriter.create<arith::AddIOp>(Op.getLoc(), newMul, newMul);

    rewriter.replaceOp(Op, newAdd);
    rewriter.eraseOp(RightDefiningOp);
    return success();
  }
};

struct PeelFromMul : public OpRewritePattern<arith::MulIOp> {
  PeelFromMul(mlir::MLIRContext *Context)
      : OpRewritePattern<arith::MulIOp>(Context, 1) {}
  LogicalResult matchAndRewrite(arith::MulIOp Op,
                                PatternRewriter &rewriter) const override {

    mlir::Value Left = Op.getOperand(0);
    mlir::Value Right = Op.getOperand(1);

    auto RightDefiningOp = Right.getDefiningOp<arith::ConstantIntOp>();
    if (!RightDefiningOp) {
      return failure();
    }

    int64_t Value = RightDefiningOp.value();

    arith::ConstantOp newConstant = rewriter.create<arith::ConstantOp>(
        RightDefiningOp.getLoc(),
        rewriter.getIntegerAttr(Right.getType(), Value - 1));
    arith::MulIOp newMul =
        rewriter.create<arith::MulIOp>(Op.getLoc(), Left, newConstant);
    arith::AddIOp newAdd =
        rewriter.create<arith::AddIOp>(Op.getLoc(), newMul, Left);

    rewriter.replaceOp(Op, newAdd);
    rewriter.eraseOp(RightDefiningOp);
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
