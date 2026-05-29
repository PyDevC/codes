import src.ir_gen as ir
import src.lowering as lowering
import src.execute as exec


def main():
    module, context, loc = ir.generate_ir(emit_ir=True)
    module = lowering.lower_to_llvm(module, context)
    # Getting lowered IR
    module.dump()

    exec.execute(module)


if __name__ == "__main__":
    main()
