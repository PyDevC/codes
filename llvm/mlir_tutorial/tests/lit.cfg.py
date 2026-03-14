import os
from pathlib import Path
from lit.formats import ShTest

config.name = "mlir_tutorial"
config.test_format = ShTest()
config.suffixes = [".mlir"]

runfiles_dir = Path(os.environ["RUNFILES_DIR"])
tool_relpaths = [
    "../../../../contrib/llvm-project/mlir"
    "../../../../contrib/llvm-project/llvm"
]

config.environment["PATH"] = (
    ":".join(str(runfiles_dir.joinpath(Path(path))) for path in tool_relpaths)
        + ":"
        + os.environ["PATH"]
)
