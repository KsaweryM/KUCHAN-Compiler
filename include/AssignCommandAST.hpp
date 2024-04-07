#ifndef ASSIGN_COMMAND_AST_HPP
#define ASSIGN_COMMAND_AST_HPP

#include "include/BinaryExpressionAST.hpp"
#include "include/CommandAST.hpp"
#include "include/VariableAST.hpp"

class AssignCommandAST : public CommandAST {
public:
  AssignCommandAST(std::shared_ptr<LLVMResourcesHolder> LLVMResources,
                   std::unique_ptr<VariableAST> variableAST,
                   std::unique_ptr<BinaryExpressionAST> expressionAST)
      : CommandAST(LLVMResources), variableAST(std::move(variableAST)),
        expressionAST(std::move(expressionAST)) {}

  virtual llvm::Value *create_code() override;

private:
  std::unique_ptr<VariableAST> variableAST;
  std::unique_ptr<BinaryExpressionAST> expressionAST;
};

#endif