#ifndef LLVM_RESOURCES_HOLDER_HPP
#define LLVM_RESOURCES_HOLDER_HPP

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <memory>
#include <map>
#include <string>
#include <iostream>

struct LLVMResourcesHolder {
    llvm::LLVMContext context;
    llvm::Module module;
    llvm::IRBuilder<> builder;
    std::map<std::string, llvm::Value *> namedValues;

    LLVMResourcesHolder() : module("KUCHAN Main module.", context), builder(context) { }
};

#endif
