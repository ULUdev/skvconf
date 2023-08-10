%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
%}

%code requires {
    #include "skvconf_types.h"
}

%define api.pure full
%define api.prefix {skvconf}
%define parse.error verbose
%parse-param {skvconf_elm_t **result}
%param {void *scanner}

%union {
    char *str;
    int num;
    bool boolean;
    skvconf_elm_t *node;
}

%code provides {
    extern int skvconflex(SKVCONFSTYPE *lval, void *s);
    int skvconferror(void *, void *, const char *);
    // int skvconferror(const char *);
    // int skvconferror(void *, const char*);
}

%token <num> NUM
%token <str> STR
%token <boolean> BOOL
%token <str> ID
%token LPAREN
%token RPAREN
%token ASSIGN
%type <node> statement start group

%destructor { free($$); } <str>
%destructor { skvconf_elm_destroy($$); } <node>

%%

start:
     statement {
     *result = $$ = $1;
     return 0;
     }
     ;

statement:
         %empty { $$ = NULL; }
         | statement ID ASSIGN NUM {
         skvconf_elm_t *e = malloc(sizeof(skvconf_elm_t));
         e->type = SKVCONF_TYPE_NUM;
         e->val.num = $4;
         e->id = $2;
         e->child = NULL;
         e->next = $1;
         $$ = e;
         }
         | statement ID ASSIGN STR {
         skvconf_elm_t *e = malloc(sizeof(skvconf_elm_t));
         e->type = SKVCONF_TYPE_STR;
         e->val.str = $4;
         e->id = $2;
         e->child = NULL;
         e->next = $1;
         $$ = e;
         }
         | statement ID ASSIGN BOOL {
         skvconf_elm_t *e = malloc(sizeof(skvconf_elm_t));
         e->type = SKVCONF_TYPE_BOOLEAN;
         e->val.boolean = $4;
         e->id = $2;
         e->child = NULL;
         e->next = $1;
         $$ = e;
         }
         | statement ID group {
         skvconf_elm_t *e = malloc(sizeof(skvconf_elm_t));
         e->type = SKVCONF_TYPE_GROUP;
         e->id = $2;
         e->child = $3;
         e->next = $1;
         $$ = e;
         }
         ;

group:
     LPAREN statement RPAREN {
        $$ = $2;
     }
     ;

%%

int skvconferror(void *v, void *s, const char *msg) {
    (void)v;
    (void)s;
    return fprintf(stderr, "parse error: %s\n", msg);
}
