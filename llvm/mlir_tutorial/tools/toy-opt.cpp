#include "lib/Transform/Affine/AffineFullUnroll.h"
#include "lib/Transform/Affine/Passes.h"
#include "lib/Transform/Arith/MulToAdd.h"
#include "lib/Transform/Arith/Passes.h"
#include "lib/Dialect/Poly/PolyDialect.h"

#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"

#include "mlir/InitAllDialects.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Pass/PassRegistry.h"
#include "mlir/Tools/mlir-opt/MlirOptMain.h"

int main(int argc, char **argv) {
  mlir::DialectRegistry registry;
  registry.insert<mlir::affine::AffineDialect>();
  registry.insert<mlir::func::FuncDialect>();
  registry.insert<mlir::arith::ArithDialect>();
  registry.insert<mlir::toy::poly::PolyDialect>();
  mlir::toy::registerAffinePasses();
  mlir::toy::registerArithPasses();
  return mlir::asMainReturnCode(mlir::MlirOptMain(argc, argv, "Toy", registry));
}
