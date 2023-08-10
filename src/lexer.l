%option noyywrap nounput noinput
%option never-interactive
%option prefix="skvconf"
%option reentrant bison-bridge
%{
#include "parser.tab.h"
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define YYSTYPE SKVCONFSTYPE
#define YY_DECL int yylex(SKVCONFSTYPE *yylval_param, yyscan_t yyscanner)
%}


%%


= {
    return ASSIGN;
}

\{ {
    return LPAREN;
}

\} {
    return RPAREN;
}

true {
    yylval->boolean = true;
    return BOOL;
}
false {
    yylval->boolean = false;
    return BOOL;
}
[[:alpha:]][[:alnum:]]* {
    yylval->str = malloc(strlen(yytext)+1);
    strncpy(yylval->str, yytext, strlen(yytext)+1);
    return ID;
}

\"[[:alnum:][:punct:] ]*\" {
    yylval->str = malloc(strlen(yytext)-1);
    strncpy(yylval->str, yytext+1, strlen(yytext)-2);
    yylval->str[strlen(yytext)-2] = '\0';
    return STR;
}

[-+]?[[:digit:]]+ {
    long n = strtol(yytext, NULL, 10);
    if (n < INT_MIN || n > INT_MAX) skvconferror(yylval, yytext, "Number out of range");
    yylval->num = n;
    return NUM;
}
[[:space:]] ;
. ;
