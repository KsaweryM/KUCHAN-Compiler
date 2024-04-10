#include "include/WhileCommandAST.hpp"
#include <llvm/IR/Constants.h>

void WhileCommandAST::parse() {
  llvm::Function *function =
      LLVMResources->builder.GetInsertBlock()->getParent();

  llvm::BasicBlock *ConditionBB =
      llvm::BasicBlock::Create(LLVMResources->context, "condition", function);
  llvm::BasicBlock *loopBeginBB =
      llvm::BasicBlock::Create(LLVMResources->context, "loop begin");
  llvm::BasicBlock *loopEndBB =
      llvm::BasicBlock::Create(LLVMResources->context, "loop end");

  LLVMResources->builder.CreateBr(ConditionBB);
  LLVMResources->builder.SetInsertPoint(ConditionBB);

  llvm::Value *condition = LLVMResources->builder.CreateICmpNE(
      conditionAST->create_code(),
      llvm::ConstantInt::get(llvm::Type::getInt32Ty(LLVMResources->context), 0),
      "if condition is not equal 0");

  LLVMResources->builder.CreateCondBr(condition, loopBeginBB, loopEndBB);

  function->insert(function->end(), loopBeginBB);
  LLVMResources->builder.SetInsertPoint(loopBeginBB);

  bodyAST->parse();

  LLVMResources->builder.CreateBr(ConditionBB);

  function->insert(function->end(), loopEndBB);
  LLVMResources->builder.SetInsertPoint(loopEndBB);
}