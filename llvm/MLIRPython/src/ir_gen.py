# Getting Dialects
from mlir.dialects import (
    func, 
    arith,
)

from mlir.ir import (
    Context,
    Module,
    Location,
    InsertionPoint,

    ## Loading Types
    IntegerType,
    FunctionType,
)

def arith_add_two_numbers():
    # Don't need to specify context
    int_type = IntegerType.get(32)
    num1 = arith.constant(int_type, 10)
    num2 = arith.constant(int_type, 20)

    total = arith.addi(num1, num2, results=[int_type])

    return total


def generate_ir(emit_ir: bool=False):
    # Setup Context
    context = Context()
    with context: ## It will add context to all operations and types inside this context
        loc = Location.unknown()
        module = Module.create(loc=loc)
        with InsertionPoint(module.body), loc:
            i32 = IntegerType.get(32)

            func_type = FunctionType.get(inputs=[], results=[i32])

            main_function = func.FuncOp("main", func_type)
            entry_block = main_function.add_entry_block()
            with InsertionPoint(entry_block):
                func_return = arith_add_two_numbers()
                func.return_([func_return])

    if emit_ir:
        module.dump()

    return module, context, loc
