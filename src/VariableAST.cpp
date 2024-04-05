#include "include/VariableAST.hpp"

llvm::Value* VariableAST::create_code()
{
    llvm::GlobalVariable* globalVariable = LLVMResources->module.getGlobalVariable(*variableName);

    if (globalVariable == nullptr)
    {
        globalVariable = new llvm::GlobalVariable(
            llvm::Type::getInt32Ty(LLVMResources->context),
            false,
            llvm::GlobalValue::ExternalLinkage,
            0,
            *variableName
        );

        LLVMResources->module.insertGlobalVariable(globalVariable);
    }

    return globalVariable;
}

void VariableAST::print(std::ostream& os) const
{
    os << "NumberAST(" << *variableName << ")";
}