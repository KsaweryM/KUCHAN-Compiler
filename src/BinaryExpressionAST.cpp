#include "include/BinaryExpressionAST.hpp"

llvm::Value* BinaryExpressionAST::create_code()
{
    llvm::Value* left_code = leftAST->create_code();
    llvm::Value* right_code = rightAST->create_code();

    if (left_code == nullptr || right_code == nullptr)
    {
        return nullptr;
    }

    llvm::Value* value = nullptr;

    switch (op)
    {
    case '+':
        value = LLVMResources->builder.CreateFAdd(left_code, right_code, "addt");
        break;
    case '-':
        value = LLVMResources->builder.CreateFSub(left_code, right_code, "sub");
        break;
    case '*':
        value = LLVMResources->builder.CreateFMul(left_code, right_code, "mul");
        break;
    case '/':
        value = LLVMResources->builder.CreateFDiv(left_code, right_code, "div");
        break;
    }

    return value;
}

void BinaryExpressionAST::print(std::ostream& os) const
{
    os << "BinaryExpressionAST(" << op << ", " << *leftAST << ", " << *rightAST << ")";
}