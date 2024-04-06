#include "include/VariableAST.hpp"
#include <cassert>

llvm::Value* VariableAST::create_code()
{
    llvm::AllocaInst* variable = LLVMResources->variables[variableName];
    assert(variable);

    return LLVMResources->builder.CreateLoad(variable->getAllocatedType(), variable, variableName.c_str());;
}

void VariableAST::print(std::ostream& os) const
{
    os << "NumberAST(" << variableName << ")";
}