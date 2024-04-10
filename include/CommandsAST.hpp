#ifndef COMMANDS_AST_HPP
#define COMMANDS_AST_HPP

#include "include/CommandAST.hpp"
#include <list>

class CommandsAST : public CommandAST {
  std::list<std::unique_ptr<CommandAST>> commands;

public:
  CommandsAST(std::shared_ptr<LLVMResourcesHolder> LLVMResources)
      : CommandAST(LLVMResources) {}

  void add_command(std::unique_ptr<CommandAST> commandAST);
  virtual void parse() override;
};

#endif