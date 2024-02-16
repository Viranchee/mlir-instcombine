// #include "llvm-c/Core.h"
// #include <algorithm>
// #include <fstream>
// #include <memory>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// #include "llvm/ADT/Statistic.h"
// #include "llvm/ADT/StringSet.h"
// #include "llvm/Analysis/InstructionSimplify.h"
// int main(int argc, char *argv[]) {
//   // ...
//   return 0;
// }
#include <iostream>

#include "mlir/IR/Dialect.h"
#include "mlir/InitAllDialects.h"
#include "mlir/InitAllPasses.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassRegistry.h"
#include "mlir/Tools/mlir-opt/MlirOptMain.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"

// docs: https://mlir.llvm.org/docs/PatternRewriter/
// arith dialect: https://mlir.llvm.org/docs/Dialects/ArithOps/
// examples: https://github.com/llvm/llvm-project/tree/main/mlir/examples

namespace mlir {

class MultiToShiftPass
    : public PassWrapper<MultiToShiftPass, OperationPass<func::FuncOp>> {
  StringRef getArgument() const final { return "instcombine"; }

  StringRef getDescription() const final {
    return "A simple shift left combiner";
  }

  void runOnOperation() override {
    const auto fnc = getOperation();
    // fnc.emitWarning() << "HERE: " << fnc;
    // func.walk([&](Operation *op) {
    // fnc->emitWarning() << "HERE: " << fnc;
    // }
  }
};

} // namespace mlir

int main(int argc, char **argv) {
  mlir::registerAllPasses();
  mlir::PassRegistration<mlir::MultiToShiftPass>();

  mlir::DialectRegistry registry;
  registerAllDialects(registry);

  return mlir::asMainReturnCode(
      mlir::MlirOptMain(argc, argv, "Custom optimizer driver\n", registry));
}
