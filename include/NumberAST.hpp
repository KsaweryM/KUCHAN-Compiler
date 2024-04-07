#ifndef NUMBER_AST_HPP
#define NUMBER_AST_HPP

#include "include/AST.hpp"
#include <iostream>

class NumberAST : public AST {
  int number;

public:
  NumberAST(std::shared_ptr<LLVMResourcesHolder> LLVMResources, int number)
      : AST(LLVMResources), number(number) {}

  virtual llvm::Value *create_code() override;

protected:
  void print(std::ostream &os) const override;
};

#endif