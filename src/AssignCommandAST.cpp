#include "include/AssignCommandAST.hpp"

void AssignCommandAST::parse() {
  llvm::Value *lValue = LLVMResources->variables[variableAST->variableName];
  llvm::Value *rValue = expressionAST->create_code();

  LLVMResources->builder.CreateStore(rValue, lValue);
}