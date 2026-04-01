// RUN: toy-opt --poly-to-standard %s | FileCheck %s

// CHECK-LABEL: test_lower_add
func.func @test_lower_add(%0: !poly.poly<10>, %1: !poly.poly<10>) -> !poly.poly<10> {
    // CHECK: arith.add
    %2 = poly.add %0, %1 : (!poly.poly<10>, !poly.poly<10>) -> !poly.poly<10>
    return %2 : !poly.poly<10>
}


