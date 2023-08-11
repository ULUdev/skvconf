#include "skvconf.h"
#include <stdio.h>
#include <string.h>
#include "parser.tab.h"
#define YYSTYPE SKVCONFSTYPE
#include "lexer.lex.h"

#define streq(s1, s2) (strlen(s1) == strlen(s2) && strncmp(s1, s2, strlen(s1)) == 0)

int skvconf_parse_file(const char *file, skvconf_elm_t **elm) {
  FILE *f = fopen(file, "r");
  if (!f) return 1;
  int res;
  yyscan_t scanner;
  if ((res = skvconflex_init(&scanner)) != 0) return res;
  skvconfset_in(f, scanner);
  res = skvconfparse(elm, scanner);
  fclose(f);
  return res;
}

skvconf_elm_t *skvconf_find_element(skvconf_elm_t *root, const char *id, int *res) {
  if (!root) {
    if (res) *res = 1;
    return NULL;
  }
  skvconf_elm_t *cur = root;
  char delim[2] = ".";
  char actual_id[strlen(id)+1];
  strncpy(actual_id, id, strlen(id));
  actual_id[strlen(id)] = '\0';
  char *cur_id = strtok(actual_id, delim);
  while (cur) {
    if (streq(cur->id, cur_id) && cur->type == SKVCONF_TYPE_GROUP) {
      cur = cur->child;
      cur_id = strtok(NULL, delim);
    } else if (streq(cur->id, cur_id)) {
      break;
    } else cur = cur->next;
  }
  if (cur) {
    if (res) *res = 0;
    return cur;
  } else {
    if (res) *res = 1;
    return NULL;
  }
}
