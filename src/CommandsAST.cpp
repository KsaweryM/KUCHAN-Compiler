#include "include/CommandsAST.hpp"

void CommandsAST::add_command(std::unique_ptr<CommandAST> commandAST) {
  commands.push_back(std::move(commandAST));
}

void CommandsAST::parse() {
  for (auto &command : commands) {
    command->parse();
  }
}