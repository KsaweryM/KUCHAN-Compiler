#include "include/VariableAST.hpp"

void VariableAST::print(std::ostream& os) const
{
    os << "NumberAST(" << *variableName << ")";
}