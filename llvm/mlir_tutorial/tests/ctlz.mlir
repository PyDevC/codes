// RUN: mlir-opt %s --convert-math-to-funcs=convert-ctlz | FileCheck %s

func.func @main(%arg0: i32) {
  %0 = math.ctlz %arg0 : i32
  func.return
}
