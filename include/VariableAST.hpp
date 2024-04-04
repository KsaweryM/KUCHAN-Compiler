#ifndef VARIABLE_AST_HPP
#define VARIABLE_AST_HPP

#include "include/AST.hpp"
#include <iostream>
#include <memory>

class VariableAST : public AST {
  std::unique_ptr<std::string> variableName;

public:
  VariableAST(std::unique_ptr<std::string> variableName) : variableName(std::move(variableName)) { }

  void print(std::ostream& os) const override;
};

#endif