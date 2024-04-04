%{
#include "include/AST.hpp"
#include "parser_y.h"


int yylex();
%}

%option noyywrap

%%
[ \t] ;
^#.*\n ;
[0-9]+  { yylval.integer = std::atoi(yytext); return TOKEN_NUMBER;   }
\*      { yylval.binary_operator = '*'; return TOKEN_MULTIPLICATION; }
\/      { yylval.binary_operator = '/'; return TOKEN_DIVISION;       }
\+      { yylval.binary_operator = '+'; return TOKEN_ADDITION;       }
\-      { yylval.binary_operator = '-'; return TOKEN_SUBTRACTION;    }
\n      { return TOKEN_END;                                          }
.       { return TOKEN_ERROR;                                        }
%%

