%{
    #include "include/AST.hpp"
    #include "include/BinaryExpressionAST.hpp"
    #include "include/NumberAST.hpp"
    #include "include/VariableAST.hpp"
    #include <iostream>
    #include <string>
    #include <memory>

    extern int yylex();
    extern int yyparse();
    extern int yylex_destroy();
    void yyerror(const char*);
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
%token <integer>           TOKEN_NUMBER
%left <binary_operator>    TOKEN_ADDITION TOKEN_SUBTRACTION
%left <binary_operator>    TOKEN_MULTIPLICATION TOKEN_DIVISION
%token <token>             TOKEN_END TOKEN_ERROR
%token <text>              TOKEN_VARIABLE;

// nonterminal symbols:
%type <ast>             input
%type <ast>             line
%type <ast>             expression
%type <binary_operator> operator
%type <ast>             value

%%
input:          %empty { }
                | input line TOKEN_END { }
;

line:           expression { $$ = $1; std::cout << *$$ << std::endl; delete $$; }
;

expression:     value { $$ = $1; }
                | expression operator expression { $$ = new BinaryExpressionAST($2,
                                                                                std::unique_ptr<AST>($1),
                                                                                std::unique_ptr<AST>($3)); }
;

operator:       TOKEN_MULTIPLICATION { $$ = $1; }
                | TOKEN_DIVISION     { $$ = $1; }
                | TOKEN_ADDITION     { $$ = $1; }
                | TOKEN_SUBTRACTION  { $$ = $1; }
;

value:          TOKEN_NUMBER     { $$ = new NumberAST($1);                                 }
                | TOKEN_VARIABLE { $$ = new VariableAST(std::unique_ptr<std::string>($1)); }
;

%%

void yyerror(const char* error) {
    std::cout << error << std::endl;
}

int main() {
    yyparse();
    yylex_destroy();
    return 0;
}