#include "include/BinaryExpressionAST.hpp"

void BinaryExpressionAST::print(std::ostream& os) const
{
    os << "BinaryExpressionAST(" << op << ", " << *leftAST << ", " << *rightAST << ")";
 }