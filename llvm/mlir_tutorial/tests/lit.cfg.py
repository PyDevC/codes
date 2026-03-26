import os
import lit.formats

config.name = "MLIR_TUTORIAL"
config.test_format = lit.formats.ShTest()
config.suffixes = [".mlir"]

test_dir = os.path.dirname(__file__)
project_root = os.path.dirname(test_dir)
# Adjust "build/bin" to match your actual build directory name
bindir = os.path.join(project_root, "build", "tools")

# 1. Update PATH so the shell can find toy-opt and FileCheck
config.environment["PATH"] = os.path.pathsep.join([
    bindir,
    os.environ.get("PATH", "")
])

# 2. Directly define the toy-opt substitution
# This replaces 'toy-opt' in your RUN lines with the full path to the binary
toy_opt_path = os.path.join(bindir, "toy-opt")
config.substitutions.append(("toy-opt", toy_opt_path))
config.substitutions.append(("FileCheck", os.path.join(os.environ["THIRDPARTY_LLVM_DIR"], "build", "bin", "FileCheck")))
