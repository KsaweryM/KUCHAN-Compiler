#include "include/AssignCommandAST.hpp"

llvm::Value *AssignCommandAST::create_code() {
  llvm::Value *lValue = LLVMResources->variables[variableAST->variableName];
  llvm::Value *rValue = expressionAST->create_code();

  return LLVMResources->builder.CreateStore(rValue, lValue);
}