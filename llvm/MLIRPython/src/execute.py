from mlir.execution_engine import ExecutionEngine
import ctypes

def execute(module):
    exec_engine = ExecutionEngine(module, opt_level=3, shared_libs=[])
    result = ctypes.c_int32(-1)
    result_ptr = ctypes.pointer(result)
    exec_engine.invoke("main", result_ptr)

    print(f"Executed: return value is {result.value}")
