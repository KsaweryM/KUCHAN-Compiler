#ifndef BINARY_EXPRESSION_AST_HPP
#define BINARY_EXPRESSION_AST_HPP

#include "include/AST.hpp"
#include <memory>
#include <iostream>

class BinaryExpressionAST : public AST {
  char op;
  std::unique_ptr<AST> leftAST, rightAST;

public:
  BinaryExpressionAST(char op,
                     std::unique_ptr<AST> leftAST,
                     std::unique_ptr<AST> rightAST)
                     : op(op), leftAST(std::move(leftAST)), rightAST(std::move(rightAST)) { }

  void print(std::ostream& os) const override;
};

#endif