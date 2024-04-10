#ifndef PRINT_COMMAND_AST_HPP
#define PRINT_COMMAND_AST_HPP

#include "include/AST.hpp"
#include "include/CommandAST.hpp"

class PrintCommandAST : public CommandAST {
public:
  PrintCommandAST(std::shared_ptr<LLVMResourcesHolder> LLVMResources,
                  std::unique_ptr<AST> value)
      : CommandAST(LLVMResources), value(std::move(value)) {}

  virtual void parse() override;

private:
  std::unique_ptr<AST> value;
};

#endif