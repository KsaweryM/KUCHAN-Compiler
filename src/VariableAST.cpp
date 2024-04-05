#include "include/VariableAST.hpp"

llvm::Value* VariableAST::create_code()
{
    return LLVMResources->namedValues[*variableName];
}

void VariableAST::print(std::ostream& os) const
{
    os << "NumberAST(" << *variableName << ")";
}