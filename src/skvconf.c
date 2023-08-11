#include "skvconf.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "parser.tab.h"
#define YYSTYPE SKVCONFSTYPE
#include "lexer.lex.h"

#define streq(s1, s2)                                                          \
  (strlen(s1) == strlen(s2) && strncmp(s1, s2, strlen(s1)) == 0)

#define strendswith(s1, s2)                                                    \
  (strlen(s1) >= strlen(s2) &&                                                 \
   strncmp(s1 + strlen(s1) - strlen(s2), s2, strlen(s2)) == 0)

/// count the occurrences of `c` in `s`
int strcount(const char *s, const char c) {
  int count = 0;
  for (int i = 0; s[i] != '\0'; i++) {
    if (c == s[i])
      count++;
  }
  return count;
}

int skvconf_parse_file(const char *file, skvconf_elm_t **elm) {
  FILE *f = fopen(file, "r");
  if (!f)
    return 1;
  int res;
  yyscan_t scanner;
  if ((res = skvconflex_init(&scanner)) != 0)
    return res;
  skvconfset_in(f, scanner);
  res = skvconfparse(elm, scanner);
  fclose(f);
  return res;
}

skvconf_elm_t *skvconf_find_element(skvconf_elm_t *root, const char *id,
                                    int *res) {
  if (!root) {
    if (res)
      *res = 1;
    return NULL;
  }
  skvconf_elm_t *cur = root;
  char delim[2] = ".";

  char actual_id[strlen(id) + 1];
  strncpy(actual_id, id, strlen(id));
  actual_id[strlen(id)] = '\0';

  char *cur_id = strtok(actual_id, delim);
  int depth = strcount(id, delim[0]);
  bool has_depth = depth ? true : false;
  while (cur && cur_id) {

    bool matches =
        (has_depth && depth == 0) ? streq(cur->id, cur_id) : streq(id, cur->id);

    /* if (has_depth && depth == 0) matches = streq(cur->id, cur_id);
    else matches = streq(id, cur->id); */

    if (streq(cur->id, cur_id) && cur->type == SKVCONF_TYPE_GROUP) {
      if (depth == 0 || !cur->child) {
        // found a group and already at lowest depth OR current group has no
        // members
        cur = NULL;
        break;
      }
      cur = cur->child;
      cur_id = strtok(NULL, delim);
      depth--;
    } else if (matches) {
      break;
    } else
      cur = cur->next;
  }
  if (cur && cur_id && depth == 0) {
    if (res)
      *res = 0;
    return cur;
  } else {
    if (res)
      *res = 1;
    return NULL;
  }
}
