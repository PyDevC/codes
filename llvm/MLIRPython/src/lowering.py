from mlir.passmanager import PassManager

def lower_to_llvm(module, context):
    with context:
        pipeline='builtin.module(convert-arith-to-llvm,convert-func-to-llvm)'
        pm = PassManager.parse(pipeline, context)

        pm.run(module.operation)

    return module
