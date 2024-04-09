#ifndef COMMAND_AST_HPP
#define COMMAND_AST_HPP

#include "include/LLVMResourcesHolder.hpp"
#include <cassert>
#include <llvm/IR/Value.h>
#include <memory>
#include <ostream>

class CommandAST {
public:
  CommandAST(std::shared_ptr<LLVMResourcesHolder> LLVMResources)
      : LLVMResources(LLVMResources) {}

  virtual ~CommandAST() = default;

  virtual void parse() {}

protected:
  std::shared_ptr<LLVMResourcesHolder> LLVMResources;
};

#endif