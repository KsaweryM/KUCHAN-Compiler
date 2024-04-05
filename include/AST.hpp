#ifndef AST_HPP
#define AST_HPP

#include "include/LLVMResourcesHolder.hpp"
#include <llvm/IR/Value.h>
#include <memory>
#include <ostream>
#include <cassert>

class AST {
public:
  AST(std::shared_ptr<LLVMResourcesHolder> LLVMResources) : LLVMResources(LLVMResources)
  {
    assert(LLVMResources);
  }

  virtual ~AST() = default;

  friend std::ostream& operator<<(std::ostream& os, const AST& ast);

  virtual llvm::Value *create_code();

protected:
  virtual void print(std::ostream& os) const;

  std::shared_ptr<LLVMResourcesHolder> LLVMResources;
};

#endif