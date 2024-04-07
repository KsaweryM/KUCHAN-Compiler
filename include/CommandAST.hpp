#ifndef COMMAND_AST_HPP
#define COMMAND_AST_HPP

#include "include/AST.hpp"

class CommandAST : public AST {
public:
  CommandAST(std::shared_ptr<LLVMResourcesHolder> LLVMResources)
      : AST(LLVMResources) {}
};

#endif