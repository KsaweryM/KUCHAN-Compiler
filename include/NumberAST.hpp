#ifndef NUMBER_AST_HPP
#define NUMBER_AST_HPP

#include "include/AST.hpp"
#include <iostream>

class NumberAST : public AST {
  int number;

public:
  NumberAST(double number) : number(number) { }

protected:
  void print(std::ostream& os) const override;
};

#endif