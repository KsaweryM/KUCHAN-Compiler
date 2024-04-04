#ifndef AST_HPP
#define AST_HPP

#include <ostream>

class AST {
public:
  virtual ~AST() = default;

  friend std::ostream& operator<<(std::ostream& os, const AST& ast);

protected:
  virtual void print(std::ostream& os) const;
};

#endif