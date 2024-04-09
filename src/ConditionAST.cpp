#include "include/ConditionAST.hpp"

llvm::Value *ConditionAST::create_code() {
  llvm::Value *left_code = leftAST->create_code();
  llvm::Value *right_code = rightAST->create_code();

  return LLVMResources->builder.CreateIntCast(
      LLVMResources->builder.CreateICmpEQ(left_code, right_code, "compare"),
      llvm::Type::getInt32Ty(LLVMResources->context), true);
}