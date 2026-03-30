// RUN: toy-opt --canonicalize %s | FileCheck %s

// CHECK-LABEL: @test_simple
func.func @test_simple() -> !poly.poly<10> {
    // CHECK: poly.constant dense<[2, 4, 6]>
    // CHECK-NEXT: return
    %0 = arith.constant dense<[1, 2, 3]> : tensor<3xi32>
    %1 = poly.from_tensor %0 : tensor<3xi32> -> !poly.poly<10>
    %2 = poly.mul %1, %1 : (!poly.poly<10>, !poly.poly<10>) -> !poly.poly<10>
    %3 = poly.mul %1, %1 : (!poly.poly<10>, !poly.poly<10>) -> !poly.poly<10>
    %4 = poly.add %2, %3 : (!poly.poly<10>, !poly.poly<10>) -> !poly.poly<10>
    return %2 : !poly.poly<10>
}
