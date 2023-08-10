/// @file
#ifndef SKVCONF_SKVCONF_H
#define SKVCONF_SKVCONF_H
#include "skvconf_types.h"
#include "parser.tab.h"
#define YYSTYPE SKVCONFSTYPE
#include "lexer.lex.h"

/// parse a config file
/// @param file the file to parse
/// @param elm a pointer to where the element should be stored
/// @return 0 if the parsing succeeded
int skvconf_parse_file(const char *file, skvconf_elm_t **elm);

/// find an element
/// @param root the element to start searching at (`should be the one returned by
/// skvconf_parse_file`)
/// @param id the id to query by. `id` is a string, where sections are delimited
/// by a period character.
/// @param res a pointer to where the result of the operation will be written.
/// If it is `NULL` it's ignored
/// @return a pointer to the element
skvconf_elm_t *skvconf_find_element(skvconf_elm_t *root, const char *id, int *res);
#endif
