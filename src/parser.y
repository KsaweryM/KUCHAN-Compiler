%{
    #include "include/AST.hpp"
    #include "include/BinaryExpressionAST.hpp"
    #include "include/LLVMResourcesHolder.hpp"
    #include "include/NumberAST.hpp"
    #include "include/VariableAST.hpp"
    #include <llvm/IR/Verifier.h>
    #include <iostream>
    #include <string>
    #include <memory>
    #include <cassert>

    extern int yylex();
    extern int yyparse();
    extern int yylex_destroy();
    void yyerror(const char*);

    std::shared_ptr<LLVMResourcesHolder> LLVMResources;
%}

%union
{
    AST* ast;
    int integer;
    char binary_operator;
    std::string* text;
    int token;
}

// terminal symbols:
%token <token>             TOKEN_VAR
%token <token>             TOKEN_BEGIN
%token <token>             TOKEN_COMMA
%token <token>             TOKEN_SEMICOLON
%token <token>             TOKEN_ASSIGN
%token <integer>           TOKEN_NUMBER
%left <binary_operator>    TOKEN_ADDITION TOKEN_SUBTRACTION
%left <binary_operator>    TOKEN_MULTIPLICATION TOKEN_DIVISION
%token <token>             TOKEN_END TOKEN_ERROR
%token <text>              TOKEN_VARIABLE_NAME;

// nonterminal symbols:
%type <ast>             program
%type <ast>             declarations
%type <ast>             commands
%type <ast>             command
%type <ast>             expression
%type <binary_operator> operator
%type <ast>             value
%type <ast>             variable

%%

program:          TOKEN_VAR declarations TOKEN_BEGIN commands TOKEN_END { }
                | TOKEN_BEGIN commands TOKEN_END { }
;

declarations:     declarations TOKEN_COMMA TOKEN_VARIABLE_NAME { }
                | TOKEN_VARIABLE_NAME { }
;

commands:         commands command { }
                | command { }
;

command:         variable TOKEN_ASSIGN expression TOKEN_SEMICOLON { VariableAST* variableAST = static_cast<VariableAST*>($1);
                                                                    llvm::Value* lValue = LLVMResources->variables[variableAST->variableName];
                                                                    llvm::Value* rValue = $3->create_code();
                                                                    LLVMResources->builder.CreateStore(rValue, lValue);
                                                                  }
;

expression:     value { $$ = $1; }
                | expression operator expression { $$ = new BinaryExpressionAST(LLVMResources,
                                                                                $2,
                                                                                std::unique_ptr<AST>($1),
                                                                                std::unique_ptr<AST>($3)); }
;

operator:       TOKEN_MULTIPLICATION { $$ = $1; }
                | TOKEN_DIVISION     { $$ = $1; }
                | TOKEN_ADDITION     { $$ = $1; }
                | TOKEN_SUBTRACTION  { $$ = $1; }
;

value:          TOKEN_NUMBER     { $$ = new NumberAST(LLVMResources, $1); }
                | variable       { $$ = $1;                               }
;

variable:       TOKEN_VARIABLE_NAME { std::string variableName(*$1); delete $1; $$ = new VariableAST(LLVMResources, variableName); }
;

%%

void yyerror(const char* error) {
    std::cout << error << std::endl;
}

int main() {
    LLVMResources = std::make_shared<LLVMResourcesHolder>();

    yyparse();

    LLVMResources->builder.CreateRetVoid();
    LLVMResources->module.print(llvm::errs(), nullptr);

    yylex_destroy();

    return 0;
}