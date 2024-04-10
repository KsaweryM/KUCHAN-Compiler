#include "include/PrintCommandAST.hpp"

void PrintCommandAST::parse() {
  llvm::PointerType *pointerType = llvm::PointerType::get(
      llvm::IntegerType::get(LLVMResources->context, 8), 0);

  llvm::FunctionType *printfType = llvm::FunctionType::get(
      LLVMResources->builder.getInt32Ty(), {pointerType}, true);
  llvm::Function *printfFunction =
      llvm::Function::Create(printfType, llvm::Function::ExternalLinkage,
                             "printf", LLVMResources->module);

  llvm::GlobalVariable *formatStr =
      LLVMResources->builder.CreateGlobalString("%d\n");

  llvm::Value *num = value->create_code();
  llvm::Value *formatPtr =
      LLVMResources->builder.CreatePointerCast(formatStr, pointerType);

  LLVMResources->builder.CreateCall(printfFunction, {formatPtr, num});
}
