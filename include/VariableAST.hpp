#ifndef VARIABLE_AST_HPP
#define VARIABLE_AST_HPP

#include "include/AST.hpp"
#include <iostream>
#include <memory>

class VariableAST : public AST {
  std::unique_ptr<std::string> variableName;

public:
  VariableAST(std::shared_ptr<LLVMResourcesHolder> LLVMResources,
              std::unique_ptr<std::string> variableName)
              : AST(LLVMResources),
                variableName(std::move(variableName)) { }

  virtual llvm::Value* create_code() override;

protected:
  void print(std::ostream& os) const override;
};

#endif