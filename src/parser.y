%{
    #include "include/AST.hpp"
    #include "include/AssignCommandAST.hpp"
    #include "include/BinaryExpressionAST.hpp"
    #include "include/CommandAST.hpp"
    #include "include/CommandsAST.hpp"
    #include "include/ConditionalCommandAST.hpp"
    #include "include/LLVMResourcesHolder.hpp"
    #include "include/NumberAST.hpp"
    #include "include/ConditionAST.hpp"
    #include "include/PrintCommandAST.hpp"
    #include "include/VariableAST.hpp"
    #include "include/WhileCommandAST.hpp"
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
    CommandAST* command;
    AST* ast;
    int integer;
    char binary_operator;
    std::string* text;
    int token;
}

// terminal symbols:
%token <token>             TOKEN_IF
%token <token>             TOKEN_THEN
%token <token>             TOKEN_ELSE
%token <token>             TOKEN_END_IF
%token <token>             TOKEN_TRUE
%token <token>             TOKEN_FALSE
%token <token>             TOKEN_VAR
%token <token>             TOKEN_BEGIN
%token <token>             TOKEN_PRINT
%token <token>             TOKEN_WHILE
%token <token>             TOKEN_WHILE_BODY_BEGIN
%token <token>             TOKEN_WHILE_BODY_END
%token <token>             TOKEN_LEFT_BRACKET
%token <token>             TOKEN_RIGHT_BRACKET
%token <token>             TOKEN_COMMA
%token <token>             TOKEN_SEMICOLON
%token <token>             TOKEN_EQUALITY
%token <token>             TOKEN_ASSIGN
%token <integer>           TOKEN_NUMBER
%left <binary_operator>    TOKEN_ADDITION TOKEN_SUBTRACTION
%left <binary_operator>    TOKEN_MULTIPLICATION TOKEN_DIVISION
%token <token>             TOKEN_END TOKEN_ERROR
%token <text>              TOKEN_VARIABLE_NAME;

// nonterminal symbols:
%type <ast>             program
%type <ast>             declarations
%type <command>         commands
%type <command>         command
%type <ast>             condition
%type <ast>             expression
%type <binary_operator> operator
%type <ast>             value
%type <ast>             variable

%%

program:          TOKEN_VAR declarations TOKEN_BEGIN commands TOKEN_END { $4->parse(); delete $4; }
                | TOKEN_BEGIN commands TOKEN_END { $2->parse(); delete $2; }
;

declarations:     declarations TOKEN_COMMA TOKEN_VARIABLE_NAME { }
                | TOKEN_VARIABLE_NAME { }
;

commands:         command           {   CommandsAST* commandsAST = new CommandsAST(LLVMResources);
                                        commandsAST->add_command(std::unique_ptr<CommandAST>($1));
                                        $$ = commandsAST;
                                    }
                | commands command  {   // Unfortunately, due to the LLVM configuration,
                                        // the use of dynamic_cast is blocked.
                                        // Below is a temporary solution.

                                        reinterpret_cast<CommandsAST*>($1)->add_command(std::unique_ptr<CommandAST>($2));
                                    }

;

command:          TOKEN_PRINT
                    TOKEN_LEFT_BRACKET
                      value
                    TOKEN_RIGHT_BRACKET
                  TOKEN_SEMICOLON                                   {   $$ = new PrintCommandAST(LLVMResources,
                                                                                   std::unique_ptr<AST>($3));
                                                                    }
                | variable TOKEN_ASSIGN expression TOKEN_SEMICOLON  {   // Unfortunately, due to the LLVM configuration,
                                                                        // the use of dynamic_cast is blocked.
                                                                        // Below is a temporary solution.
                                                                        $$ = new AssignCommandAST(LLVMResources,
                                                                                   std::unique_ptr<VariableAST>(reinterpret_cast<VariableAST*>($1)),
                                                                                   std::unique_ptr<BinaryExpressionAST>(reinterpret_cast<BinaryExpressionAST*>($3)));
                                                                    }
                | TOKEN_IF
                    TOKEN_LEFT_BRACKET
                      condition
                    TOKEN_RIGHT_BRACKET
                    TOKEN_THEN
                    commands
                  TOKEN_ELSE
                    commands
                  TOKEN_END_IF                                      {   // Unfortunately, due to the LLVM configuration,
                                                                        // the use of dynamic_cast is blocked.
                                                                        // Below is a temporary solution.

                                                                        $$ = new ConditionalCommandAST(LLVMResources,
                                                                                   std::unique_ptr<ConditionAST>(reinterpret_cast<ConditionAST*>($3)),
                                                                                   std::unique_ptr<CommandAST>(reinterpret_cast<CommandAST*>($6)),
                                                                                   std::unique_ptr<CommandAST>(reinterpret_cast<CommandAST*>($8)));
                                                                    }
                | TOKEN_WHILE
                    TOKEN_LEFT_BRACKET
                      condition
                    TOKEN_RIGHT_BRACKET
                    TOKEN_WHILE_BODY_BEGIN
                      commands
                    TOKEN_WHILE_BODY_END                            {   // Unfortunately, due to the LLVM configuration,
                                                                        // the use of dynamic_cast is blocked.
                                                                        // Below is a temporary solution.

                                                                        $$ = new WhileCommandAST(LLVMResources,
                                                                                   std::unique_ptr<ConditionAST>(reinterpret_cast<ConditionAST*>($3)),
                                                                                   std::unique_ptr<CommandAST>(reinterpret_cast<CommandAST*>($6)));
                                                                    }
;

condition:        expression TOKEN_EQUALITY expression  { $$ = new ConditionAST(LLVMResources,
                                                                     std::unique_ptr<AST>($1),
                                                                     std::unique_ptr<AST>($3));
                                                        }
;

expression:       value { $$ = $1; }
                | expression operator expression    { $$ = new BinaryExpressionAST(LLVMResources,
                                                                 $2,
                                                                 std::unique_ptr<AST>($1),
                                                                 std::unique_ptr<AST>($3));
                                                    }
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