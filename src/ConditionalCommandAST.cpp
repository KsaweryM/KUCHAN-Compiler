#include "include/ConditionalCommandAST.hpp"
#include <cassert>
#include <llvm/IR/Constants.h>

void ConditionalCommandAST::parse() {
  llvm::Value *condition = LLVMResources->builder.CreateICmpNE(
      conditionAST->create_code(),
      llvm::ConstantInt::get(llvm::Type::getInt32Ty(LLVMResources->context), 0),
      "if condition is not equal 0");

  llvm::Function *function =
      LLVMResources->builder.GetInsertBlock()->getParent();

  llvm::BasicBlock *ThenBB =
      llvm::BasicBlock::Create(LLVMResources->context, "then", function);
  llvm::BasicBlock *ElseBB =
      llvm::BasicBlock::Create(LLVMResources->context, "else");
  llvm::BasicBlock *MergeBB =
      llvm::BasicBlock::Create(LLVMResources->context, "merge block");

  LLVMResources->builder.CreateCondBr(condition, ThenBB, ElseBB);

  LLVMResources->builder.SetInsertPoint(ThenBB);
  thenAST->parse();

  LLVMResources->builder.CreateBr(MergeBB);

  function->insert(function->end(), ElseBB);

  LLVMResources->builder.SetInsertPoint(ElseBB);

  elseAST->parse();

  LLVMResources->builder.CreateBr(MergeBB);

  function->insert(function->end(), MergeBB);

  LLVMResources->builder.SetInsertPoint(MergeBB);
}