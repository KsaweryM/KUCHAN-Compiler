#include "include/NumberAST.hpp"
#include <llvm/IR/Constants.h>

llvm::Value *NumberAST::create_code() {
  const int numBits = 32;
  return llvm::ConstantInt::get(LLVMResources->context,
                                llvm::APInt(numBits, number));
}

void NumberAST::print(std::ostream &os) const {
  os << "NumberAST(" << number << ")";
}