#include "lib/Conversion/PolyToStandard/PolyToStandard.h"

#include "lib/Dialect/Poly/PolyOps.h"
#include "lib/Dialect/Poly/PolyType.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Func/Transforms/FuncConversions.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/IR/ImplicitLocOpBuilder.h"
#include "mlir/Transforms/DialectConversion.h"
#include "llvm/ADT/SmallVector.h"

namespace mlir {
namespace toy {
namespace poly {

#define GEN_PASS_DEF_POLYTOSTANDARD
#include "lib/Conversion/PolyToStandard/PolyToStandard.h.inc"

class PolyToStandardTypeConverter : public TypeConverter {
public:
  PolyToStandardTypeConverter(MLIRContext *context) {
    addConversion([](Type type) { return type; });
    addConversion([context](PolynomialType type) -> Type {
      int degreeBound = type.getDecimalBound();
      IntegerType elementType = IntegerType::get(
          context, 32, IntegerType::SignednessSemantics::Signless);
      return RankedTensorType::get({degreeBound}, elementType);
    });
  }
};

struct ConvertAdd : public OpConversionPattern<AddOp> {
  ConvertAdd(MLIRContext *context) : OpConversionPattern<AddOp>(context) {};
  using OpConversionPattern::OpConversionPattern;
  LogicalResult
  matchAndRewrite(AddOp Op, OpAdaptor adaptor,
                  ConversionPatternRewriter &rewriter) const override {
    arith::AddIOp addop = rewriter.create<arith::AddIOp>(
        Op.getLoc(), adaptor.getLhs(), adaptor.getRhs());

    rewriter.replaceOp(Op.getOperation(), addop.getOperation());
    return llvm::success();
  }
};

struct ConvertSub : public OpConversionPattern<SubOp> {
  ConvertSub(MLIRContext *context) : OpConversionPattern<SubOp>(context) {};
  using OpConversionPattern::OpConversionPattern;
  LogicalResult
  matchAndRewrite(SubOp Op, SubOp::Adaptor adaptor,
                  ConversionPatternRewriter &rewriter) const override {
    arith::SubIOp subop = rewriter.create<arith::SubIOp>(
        Op.getLoc(), adaptor.getLhs(), adaptor.getRhs());

    rewriter.replaceOp(Op.getOperation(), subop.getOperation());
    return llvm::success();
  }
};

struct ConvertFromTensor : public OpConversionPattern<FromTensorOp> {
  ConvertFromTensor(MLIRContext *context)
      : OpConversionPattern<FromTensorOp>(context) {};
  using OpConversionPattern::OpConversionPattern;
  LogicalResult matchAndRewrite(FromTensorOp Op, FromTensorOp::Adaptor adaptor,
                                ConversionPatternRewriter &rewriter) {
    auto resultTensorTy =
        cast<RankedTensorType>(typeConverter->convertType(Op.getType()));
    auto resultshape = resultTensorTy.getShape();
    auto resultEltTy = resultTensorTy.getElementType();
    auto inputTensorTy = Op.getInput().getType();
    auto inputshape = inputTensorTy.getShape();

    ImplicitLocOpBuilder b(Op.getLoc(), rewriter);
    auto coeffval = adaptor.getInput();
    if (inputshape < resultshape) {
      llvm::SmallVector<OpFoldResult, 1> low, high;
      low.push_back(rewriter.getIndexAttr(0));
      high.push_back(
          rewriter.getIndexAttr(resultshape.size() - inputshape.size()));
      coeffval = b.create<tensor::PadOp>(
          resultTensorTy, coeffval, low, high,
          b.create<arith::ConstantOp>(rewriter.getIntegerAttr(resultEltTy, 0)),
          false);
    }

    rewriter.replaceOp(Op, coeffval);
    return llvm::success();
  }
};

struct ConvertToTensor : OpConversionPattern<ToTensorOp> {
  ConvertToTensor(MLIRContext *context)
      : OpConversionPattern<ToTensorOp>(context) {}

  using OpConversionPattern::OpConversionPattern;

  LogicalResult
  matchAndRewrite(ToTensorOp Op, ToTensorOp::Adaptor adaptor,
                  ConversionPatternRewriter &rewriter) const override {
    rewriter.replaceOp(Op, adaptor.getInput());
    return llvm::success();
  }
};

struct ConvertConstant : OpConversionPattern<ConstantOp> {
  ConvertConstant(MLIRContext *context) : OpConversionPattern(context) {};
  LogicalResult
  matchAndRewrite(ConstantOp Op, ConstantOp::Adaptor adaptor,
                  ConversionPatternRewriter &rewriter) const override {
    ImplicitLocOpBuilder b(Op.getLoc(), rewriter);
    auto constOp = b.create<arith::ConstantOp>(adaptor.getCoefficient());
    auto fromTensorOp =
        b.create<FromTensorOp>(Op.getResult().getType(), constOp);
    rewriter.replaceOp(Op, fromTensorOp.getResult());
    return llvm::success();
  }
};

struct ConvertMul : OpConversionPattern<MulOp> {
  ConvertMul(MLIRContext *context) : OpConversionPattern(context) {};
  using OpConversionPattern::OpConversionPattern;

  LogicalResult
  matchAndRewrite(MulOp Op, MulOp::Adaptor adaptor,
                  ConversionPatternRewriter &rewriter) const override {
    auto polyMulTensorType = cast<RankedTensorType>(adaptor.getLhs().getType());
    auto numTerms = polyMulTensorType.getShape()[0];
    ImplicitLocOpBuilder b(Op.getLoc(), rewriter);
    auto polyMulResults = b.create<arith::ConstantOp>(
        polyMulTensorType, DenseElementsAttr::get(polyMulTensorType, 0));
    auto lowerBound =
        b.create<arith::ConstantOp>(b.getIndexType(), b.getIndexAttr(0));
    auto numTermsOps =
        b.create<arith::ConstantOp>(b.getIndexType(), b.getIndexAttr(numTerms));
    auto step =
        b.create<arith::ConstantOp>(b.getIndexType(), b.getIndexAttr(1));
    auto p0 = adaptor.getLhs();
    auto p1 = adaptor.getRhs();

    auto outerloop = b.create<scf::ForOp>(
        lowerBound, numTermsOps, step, ValueRange(polyMulResults.getResult()),
        [&](OpBuilder &builder, Location loc, Value p0Index,
            ValueRange loopState) {
          ImplicitLocOpBuilder b(Op.getLoc(), builder);
          auto innerloop = b.create<scf::ForOp>(
              lowerBound, numTermsOps, step, loopState,
              [&](OpBuilder &builder, Location loc, Value p1Index,
                  ValueRange loopState) {
                ImplicitLocOpBuilder b(Op.getLoc(), builder);
                auto accumTensor = loopState.front();
                auto destIndex = b.create<arith::RemUIOp>(
                    b.create<arith::AddIOp>(p0Index, p1Index), numTermsOps);
                auto mulOp = b.create<arith::MulIOp>(
                    b.create<tensor::ExtractOp>(p0, ValueRange(p0Index)),
                    b.create<tensor::ExtractOp>(p1, ValueRange(p1Index)));
                auto result = b.create<arith::AddIOp>(
                    mulOp, b.create<tensor::ExtractOp>(accumTensor,
                                                       destIndex.getResult()));
                auto stored = b.create<tensor::InsertOp>(result, accumTensor,
                                                         destIndex.getResult());
                b.create<scf::YieldOp>(stored.getResult());
              });
          b.create<scf::YieldOp>(innerloop.getResults());
        });
    rewriter.replaceOp(Op, outerloop.getResult(0));
    return llvm::success();
  }
};

struct ConvertEval : public OpConversionPattern<EvalOp> {
  ConvertEval(MLIRContext *context) : OpConversionPattern(context) {}
  using OpConversionPattern::OpConversionPattern;
  LogicalResult
  matchAndRewrite(EvalOp Op, EvalOp::Adaptor adaptor,
                  ConversionPatternRewriter &rewriter) const override {
    auto polyTensorType =
        cast<RankedTensorType>(adaptor.getPolynomial().getType());
    auto numTerms = polyTensorType.getShape()[0];
    ImplicitLocOpBuilder b(Op.getLoc(), rewriter);
    auto lowerBound =
        b.create<arith::ConstantOp>(b.getIndexType(), b.getIndexAttr(1));
    auto numTermsOp = b.create<arith::ConstantOp>(b.getIndexType(),
                                                  b.getIndexAttr(numTerms + 1));
    auto step = lowerBound;

    auto poly = adaptor.getPolynomial();
    auto point = adaptor.getPoint();

    auto accum =
        b.create<arith::ConstantOp>(b.getI32Type(), b.getI32IntegerAttr(0));
    auto loop = b.create<scf::ForOp>(
        lowerBound, numTermsOp, step, accum.getResult(),
        [&](OpBuilder &builder, Location loc, Value loopIndex,
            ValueRange loopState) {
          ImplicitLocOpBuilder b(Op.getLoc(), builder);
          auto accum = loopState.front();
          auto coeffIndex = b.create<arith::SubIOp>(numTermsOp, loopIndex);
          auto mulOp = b.create<arith::MulIOp>(point, accum);
          auto result = b.create<arith::AddIOp>(
              mulOp, b.create<tensor::ExtractOp>(poly, coeffIndex.getResult()));
          b.create<scf::YieldOp>(result.getResult());
        });

    rewriter.replaceOp(Op, loop.getResult(0));
    return success();
  }
};

struct PolyToStandard : impl::PolyToStandardBase<PolyToStandard> {
  using PolyToStandardBase::PolyToStandardBase;
  void runOnOperation() override {
    MLIRContext *context = &getContext();
    auto *module = getOperation();
    ConversionTarget target(*context);
    target.addLegalDialect<arith::ArithDialect>();
    target.addLegalDialect<scf::SCFDialect>();
    target.addLegalDialect<func::FuncDialect>();
    target.addLegalDialect<tensor::TensorDialect>();
    target.addIllegalDialect<PolyDialect>();
    RewritePatternSet patterns(context);
    PolyToStandardTypeConverter typeConverter(context);
    patterns.add<ConvertAdd, ConvertSub, ConvertFromTensor, ConvertToTensor,
                 ConvertConstant, ConvertMul, ConvertEval>(context);

    populateFunctionOpInterfaceTypeConversionPattern<func::FuncOp>(
        patterns, typeConverter);
    target.addDynamicallyLegalOp<func::FuncOp>([&](func::FuncOp Op) {
      return typeConverter.isSignatureLegal(Op.getFunctionType()) &&
             typeConverter.isLegal(&Op.getBody());
    });

    populateReturnOpTypeConversionPattern(patterns, typeConverter);
    target.addDynamicallyLegalOp<func::FuncOp>(
        [&](func::FuncOp Op) { return typeConverter.isLegal(Op); });

    populateCallOpTypeConversionPattern(patterns, typeConverter);
    target.addDynamicallyLegalOp<func::CallOp>(
        [&](func::CallOp Op) { return typeConverter.isLegal(Op); });

    populateBranchOpInterfaceTypeConversionPattern(patterns, typeConverter);
    target.markUnknownOpDynamicallyLegal([&](Operation *Op) {
      return isNotBranchOpInterfaceOrReturnLikeOp(Op) ||
             isLegalForBranchOpInterfaceTypeConversionPattern(Op,
                                                              typeConverter) ||
             isLegalForReturnOpTypeConversionPattern(Op, typeConverter);
    });

    if (failed(applyPartialConversion(module, target, std::move(patterns)))) {
      signalPassFailure();
    }
  }
};

} // namespace poly
} // namespace toy
} // namespace mlir
