#include "include/AST.hpp"

void AST::print(std::ostream& os) const
{
    os << "AST()";
}

std::ostream& operator<<(std::ostream& os, const AST& ast)
{
    ast.print(os);

    return os;
}