#include "lib/Transform/Affine/AffineFullUnroll.h"
#include "lib/Transform/Arith/MulToAdd.h"
#include "mlir/InitAllDialects.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Pass/PassRegistry.h"
#include "mlir/Tools/mlir-opt/MlirOptMain.h"

int main(int argc, char **argv) {
  mlir::DialectRegistry registry;
  // mlir::registerAllDialects(registry);
  registry.insert<mlir::affine::AffineDialect>();
  registry.insert<mlir::func::FuncDialect>();
  registry.insert<mlir::arith::ArithDialect>();
  mlir::PassRegistration<mlir::toy::AffineFullUnrollPass>();
  mlir::PassRegistration<mlir::toy::AffineFullUnrollPassAsPatternRewrite>();
  mlir::PassRegistration<mlir::toy::MulToAddPass>();
  return mlir::asMainReturnCode(mlir::MlirOptMain(argc, argv, "Toy", registry));
}
