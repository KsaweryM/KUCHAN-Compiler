#include "include/PrintCommandAST.hpp"

void PrintCommandAST::parse() {
  // The variables have been temporarily set as static.
  // It will be corrected once support for functions is implemented.

  static llvm::PointerType *pointerType = llvm::PointerType::get(
      llvm::IntegerType::get(LLVMResources->context, 8), 0);

  static llvm::FunctionType *printfType = llvm::FunctionType::get(
      LLVMResources->builder.getInt32Ty(), {pointerType}, true);

  static llvm::Function *printfFunction =
      llvm::Function::Create(printfType, llvm::Function::ExternalLinkage,
                             "printf", LLVMResources->module);

  static llvm::GlobalVariable *formatStr =
      LLVMResources->builder.CreateGlobalString("%d\n");

  llvm::Value *num = value->create_code();
  llvm::Value *formatPtr =
      LLVMResources->builder.CreatePointerCast(formatStr, pointerType);

  LLVMResources->builder.CreateCall(printfFunction, {formatPtr, num});
}
