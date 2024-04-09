#ifndef CONDITIONAL_COMMAND_AST_HPP
#define CONDITIONAL_COMMAND_AST_HPP

#include "include/BinaryExpressionAST.hpp"
#include "include/CommandAST.hpp"

class ConditionalCommandAST : public CommandAST {
  std::unique_ptr<BinaryExpressionAST> conditionAST;
  std::unique_ptr<CommandAST> thenAST;
  std::unique_ptr<CommandAST> elseAST;

public:
  ConditionalCommandAST(std::shared_ptr<LLVMResourcesHolder> LLVMResources,
                        std::unique_ptr<BinaryExpressionAST> conditionAST,
                        std::unique_ptr<CommandAST> thenAST,
                        std::unique_ptr<CommandAST> elseAST)
      : CommandAST(LLVMResources), conditionAST(std::move(conditionAST)),
        thenAST(std::move(thenAST)), elseAST(std::move(elseAST)) {}

  virtual void parse() override;
};

#endif