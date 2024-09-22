// LogicalResult matchAndRewrite(ShLIOp inst4,
//                               PatternRewriter &rewriter) const override {

//   // 1. %c4_i32 = arith.constant 4      : i32
//   // 2. %c16_i32 = arith.constant 16    : i32
//   // 3. %0 = arith.shli %arg0, %c4_i32  : i32
//   // 4. %1 = arith.shli %0,   %c16_i32  : i32    <--- Match works for this

//   // Check if the shifter is a constant
//   auto inst2 = inst4.getOperand(1).getDefiningOp<ConstantIntOp>();
//   if (!inst2) {
//     return failure();
//   }
//   auto inst3 = inst4.getOperand(0).getDefiningOp<ShLIOp>();
//   if (!inst3) {
//     return failure();
//   }
//   // Check if the shifter is a constant
//   auto inst1 = inst3.getOperand(1).getDefiningOp<ConstantIntOp>();
//   if (!inst1) {
//     return failure();
//   }
//   const auto width = inst1.getType().getIntOrFloatBitWidth();

//   // Now that the shifters are constants, add them and make a new shifter
//   const int64_t shiftAmount = inst1.value() + inst2.value();

//   if (shiftAmount > width) {
//     // Overflow of shifting. Do not optimize
//     // TODO: Can return 0 too for optimization
//     return failure();
//   }

//   // change value of inst1 to shiftAmount
//   inst1.setValueAttr(
//       rewriter.getIntegerAttr(rewriter.getIntegerType(width),
//       shiftAmount));

//   // auto combinedConstant =
//   //     rewriter.create<ConstantIntOp>(inst1->getLoc(), shiftAmount,
//   width);
//   // auto val = inst3.getOperand(0);
//   // ShLIOp newShl =
//   //     rewriter.create<ShLIOp>(inst4.getLoc(), val, combinedConstant);

//   // rewriter.replaceOp(inst1, combinedConstant);
//   rewriter.eraseOp(inst1);
//   // rewriter.replaceOp(inst4, newShl);
//   // rewriter.eraseOp(inst4);
//   // rewriter.eraseOp(inst2);
//   // rewriter.eraseOp(inst3);

//   return success();
// }
