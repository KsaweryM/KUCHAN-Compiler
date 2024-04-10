#ifndef WHILE_COMMAND_AST_HPP
#define WHILE_COMMAND_AST_HPP

#include "include/CommandAST.hpp"
#include "include/ConditionAST.hpp"

class WhileCommandAST : public CommandAST {
  std::unique_ptr<ConditionAST> conditionAST;
  std::unique_ptr<CommandAST> bodyAST;

public:
  WhileCommandAST(std::shared_ptr<LLVMResourcesHolder> LLVMResources,
                  std::unique_ptr<ConditionAST> conditionAST,
                  std::unique_ptr<CommandAST> bodyAST)
      : CommandAST(LLVMResources), conditionAST(std::move(conditionAST)),
        bodyAST(std::move(bodyAST)) {}

  virtual void parse() override;
};

#endif