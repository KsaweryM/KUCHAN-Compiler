#include "include/AST.hpp"

llvm::Value* AST::create_code()
{
    return nullptr;
}

void AST::print(std::ostream& os) const
{
    os << "AST()";
}

std::ostream& operator<<(std::ostream& os, const AST& ast)
{
    ast.print(os);

    return os;
}