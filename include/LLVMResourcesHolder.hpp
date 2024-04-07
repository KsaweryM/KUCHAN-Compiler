#ifndef LLVM_RESOURCES_HOLDER_HPP
#define LLVM_RESOURCES_HOLDER_HPP

#include <iostream>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <map>
#include <memory>
#include <string>

struct LLVMResourcesHolder {
  llvm::LLVMContext context;
  llvm::Module module;
  llvm::IRBuilder<> builder;
  llvm::Function *mainFunction;
  std::map<std::string, llvm::AllocaInst *> variables;

  LLVMResourcesHolder()
      : module("KUCHAN Main module.", context), builder(context) {
    mainFunction = llvm::Function::Create(
        llvm::FunctionType::get(llvm::Type::getVoidTy(context), false),
        llvm::Function::ExternalLinkage, "main", module);
    builder.SetInsertPoint(
        llvm::BasicBlock::Create(context, "firstBasicBlock", mainFunction));
  }

  // Temporary function.
  void print() { module.print(llvm::outs(), nullptr); }
};

#endif
