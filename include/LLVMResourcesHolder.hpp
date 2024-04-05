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

    LLVMResourcesHolder() : module("KUCHAN Main module.", context), builder(context) { }

    // Temporary function.
    void print()
    {
        module.print(llvm::outs(), nullptr);
    }
};

#endif
