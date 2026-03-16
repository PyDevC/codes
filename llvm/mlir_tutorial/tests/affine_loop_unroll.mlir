// RUN: toy-opt %s --affine-full-unroll > %t
// RUN: FileCheck %s < %t

func.func @test_single_nested_loop(%buffer: memref<4xi32>) -> (i32) {
    %sum_0 = arith.constant 0 : i32
    // CHECK-NOT: affine.for
    %sum = affine.for %i = 0 to 4 iter_args(%sum_iter = %sum_0) -> (i32) {
        %t = affine.load %buffer[i] : memref<4xi32>
        %sum_next = arith.addi %sum_iter, %t : i32
        affine.yield %sum_next : i32
    }
    return %sum_0 : i32
}

func.func. @test_double_nested_loop (%buffer: memref<4x3xi32>) -> (i32) {
    %sum_outer_0 = arith.constant 0 : i32
    // CHECK-NOT: affine.for
    %sum = affine.for %i = 0 to 4 iter_args(%sum_iter = %sum_outer_0) -> (i32) {
        %sum_inner_0 = arith.constant 0 : i32
        // CHECK-NOT: affine.for
        %sum_inner = affine.for %j = 0 to 3 iter_args(%sum_inner_iter = %sum_inner_0) -> (i32) {
            %t = affine.load %buffer[i][j] : memref<4x3xi32>
            %sum_inner_next = arith.addi %sum_inner_iter, %t : i32
            affine.yield %sum_inner_next : i32
        }
        %sum_next = arith.addi %sum_iter, %sum_inner : i32
        affine.yield %sum_next : i32
    }
    return sum_0 : i32
}

