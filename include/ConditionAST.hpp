#ifndef CONDITION_AST_HPP
#define CONDITION_AST_HPP

#include "include/AST.hpp"
#include <iostream>
#include <memory>

class ConditionAST : public AST {
  std::unique_ptr<AST> leftAST, rightAST;

public:
  ConditionAST(std::shared_ptr<LLVMResourcesHolder> LLVMResources,
               std::unique_ptr<AST> leftAST, std::unique_ptr<AST> rightAST)
      : AST(LLVMResources), leftAST(std::move(leftAST)),
        rightAST(std::move(rightAST)) {}

  virtual llvm::Value *create_code() override;
};

#endif