#ifndef VARIABLE_AST_HPP
#define VARIABLE_AST_HPP

#include "include/AST.hpp"
#include <iostream>
#include <memory>

class VariableAST : public AST {
public:
  std::string variableName;

  VariableAST(std::shared_ptr<LLVMResourcesHolder> LLVMResources,
              std::string VariableName)
              : AST(LLVMResources),
                variableName(std::move(VariableName)) {

    llvm::AllocaInst* variable = LLVMResources->variables[variableName];

    if (variable == nullptr)
    {
        llvm::IRBuilder<> temporaryBuilder(&LLVMResources->mainFunction->getEntryBlock(),
                                            LLVMResources->mainFunction->getEntryBlock().begin());
        variable = temporaryBuilder.CreateAlloca(llvm::Type::getInt32Ty(LLVMResources->context), nullptr,
                                                 variableName);

        LLVMResources->variables[variableName] = variable;
    }
  }

  virtual llvm::Value* create_code() override;

protected:
  void print(std::ostream& os) const override;
};

#endif