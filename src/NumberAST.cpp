#include "include/NumberAST.hpp"

void NumberAST::print(std::ostream& os) const
{
    os << "NumberAST(" << number << ")";
}