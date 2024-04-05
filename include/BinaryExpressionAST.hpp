#ifndef BINARY_EXPRESSION_AST_HPP
#define BINARY_EXPRESSION_AST_HPP

#include "include/AST.hpp"
#include <memory>
#include <iostream>

class BinaryExpressionAST : public AST {
  char op;
  std::unique_ptr<AST> leftAST, rightAST;

public:
  BinaryExpressionAST(std::shared_ptr<LLVMResourcesHolder> LLVMResources,
                      char op,
                      std::unique_ptr<AST> leftAST,
                      std::unique_ptr<AST> rightAST)
                      : AST(LLVMResources), op(op),
                        leftAST(std::move(leftAST)),
                        rightAST(std::move(rightAST)) { }

virtual llvm::Value* create_code() override;

protected:
  void print(std::ostream& os) const override;
};

#endif