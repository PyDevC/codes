from mlir.execution_engine import ExecutionEngine
import ctypes

def execute(module, context):
    with context:
        exec_engine = ExecutionEngine(module, opt_level=3)
        result = (ctypes.c_int32 * 1)(-1)
        exec_engine.invoke("main", result)

    print(f"Executed: return value is {result[0]}")
