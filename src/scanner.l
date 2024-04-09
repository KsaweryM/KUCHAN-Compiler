%{
#include "include/AST.hpp"
#include "include/CommandAST.hpp"
#include <string>
#include "parser_y.h"

int yylex();
%}

%option noyywrap

%%
[ \t] ;
^#.*\n ;
"IF"                 { return TOKEN_IF;                                                           }
"THEN"               { return TOKEN_THEN;                                                         }
"ELSE"               { return TOKEN_ELSE;                                                         }
"FI"                 { return TOKEN_END_IF;                                                       }
"TRUE"               { return TOKEN_TRUE;                                                         }
"FALSE"              { return TOKEN_FALSE;                                                        }
"VAR"                { return TOKEN_VAR;                                                          }
"BEGIN"              { return TOKEN_BEGIN;                                                        }
"END"                { return TOKEN_END;                                                          }
","                  { return TOKEN_COMMA;                                                        }
";"                  { return TOKEN_SEMICOLON;                                                    }
"=="                 { return TOKEN_EQUALITY;                                                     }
"="                  { return TOKEN_ASSIGN;                                                       }
"*"                  { yylval.binary_operator = '*'; return TOKEN_MULTIPLICATION;                 }
"/"                  { yylval.binary_operator = '/'; return TOKEN_DIVISION;                       }
"+"                  { yylval.binary_operator = '+'; return TOKEN_ADDITION;                       }
"-"                  { yylval.binary_operator = '-'; return TOKEN_SUBTRACTION;                    }
"n"                  { return TOKEN_END;                                                          }
[0-9]+               { yylval.integer = std::atoi(yytext); return TOKEN_NUMBER;                   }
[A-Za-z][A-Za-z0-9]* { yylval.text = new std::string(yytext, yyleng); return TOKEN_VARIABLE_NAME; }
.                    { return TOKEN_ERROR;                                                        }
%%

